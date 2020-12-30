#include <WinSock2.h>
#include <cstring>
#include<string.h>
#include<vector>
#include "rapidjson/prettywriter.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;
using namespace rapidjson;

struct Param {
	std::string Name;
	std::string Content;
};

struct RequestPacket {
	int PacketID;
	int TotalLength;
	int MethodID;
	std::vector<Param> Params;
};

struct ResponsePacket {
	int PacketID;
	int StatusCode;
	int TotalLength;
	std::string Content;
};

class Protocol {
public:
	Protocol(std::string ip, int port);
	bool Connect();
	bool Disconnect();
	bool Ping(std::string Info);
	void run();
	void analyseRequests(RequestPacket req);

private:
	char buf[1024];
	bool Connected;
	int TargetPort;
	char* position;
	std::string IPAddress;
	SOCKET Socket;
	RequestPacket GetNextPacket();
	ResponsePacket GenerateResponse(int PacketID, int StatusCode, std::string Content);
	void read(int length, char* buf);
	bool sendPacket(ResponsePacket resp);
};

