<template>
  <el-header>
    <el-row class="header-top">
      <el-col :span="12">
        <el-breadcrumb separator-class="el-icon-arrow-right">
          <el-breadcrumb-item :to="{ path: '/' }">首页</el-breadcrumb-item>
          <el-breadcrumb-item>活动管理</el-breadcrumb-item>
          <el-breadcrumb-item>活动列表</el-breadcrumb-item>
          <el-breadcrumb-item>活动详情</el-breadcrumb-item>
        </el-breadcrumb>
      </el-col>
      <el-col :span="12">
        <el-dropdown>
          <span class="el-dropdown-link cursor-hand">
            王小虎<i class="el-icon-setting setting-rigth"></i>
          </span>
          <el-dropdown-menu slot="dropdown">
            <el-dropdown-item>查看</el-dropdown-item>
            <el-dropdown-item>新增</el-dropdown-item>
            <el-dropdown-item>删除</el-dropdown-item>
          </el-dropdown-menu>
        </el-dropdown>
      </el-col>
    </el-row>
  </el-header>
</template>

<script>
export default {
  name: 'ZnHeader',
  data() {
    return {}
  },
  methods: {}
}
</script>

<style>
.el-header {
  color: #333;
  text-align: right;
  background: transparent;
  border-bottom: 1px solid #fefefe;
}
.header-top {
  margin-top: 20px;
}
.el-dropdown {
  vertical-align: top;
}
.cursor-hand {
  cursor: pointer;
}
.setting-rigth {
  padding-left: 5px;
}
</style>
