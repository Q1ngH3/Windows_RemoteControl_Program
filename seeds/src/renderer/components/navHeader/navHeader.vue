<template>
    <div class="navHeader">
        <Titlebtn type="min" class="el-icon-remove-outline">
        </Titlebtn>
        <Titlebtn type="max" class="el-icon-circle-plus-outline">
        </Titlebtn>
        <Titlebtn type="close" class="el-icon-circle-close">
        </Titlebtn>
    </div>
</template>

<script>
    import Titlebtn from '@/components/navHeader/Titlebtn'

export default {
      name: 'navHeader',
      components: {
        Titlebtn
      }
    }
</script>

<style>
.navHeader {
    left: 200px;
    position: absolute;
    width: 81%;
    height: 60px;
    box-sizing: border-box;
    background-color: #edf2f4;
    -webkit-app-region: drag;
    padding: 0;
    margin: 0;
}
</style>
