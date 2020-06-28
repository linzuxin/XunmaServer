<template>
  <div id="app">
    <el-container>
      <zn-menu />
      <el-container>
        <zn-header />
        <el-main>
          <router-view />
        </el-main>
        <el-footer>Footer</el-footer>
      </el-container>
    </el-container>
  </div>
</template>

<script>
import ZnMenu from '@/components/zn_menu'
import ZnHeader from '@/components/zn_header'

export default {
  name: 'App',
  components: {
    ZnMenu,
    ZnHeader
  }
}
</script>

<style>
html,
body {
  padding: 0px;
  margin: 0px;
  height: 100%;
}
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  color: #2c3e50;
  height: 100%;
}
.el-footer {
  background-color: transparent;
  text-align: center;
  line-height: 60px;
}

.el-main {
  background-color:rgb(255, 255, 255);
  color: #333;
  text-align: center;
  overflow: hidden;
  height: 100%;
  box-shadow: 0px 2px 8px 8px rgba(0, 0, 0, 0.03);
  border:1px solid #efefef;
}

#app > .el-container {
  height: 100%;
}

body > .el-container {
  margin-bottom: 40px;
}

.el-container:nth-child(5) .el-aside,
.el-container:nth-child(6) .el-aside {
  line-height: 260px;
}

.el-container:nth-child(7) .el-aside {
  line-height: 320px;
}
</style>
