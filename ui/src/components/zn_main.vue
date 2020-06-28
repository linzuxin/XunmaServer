<template>
  <div class="main_border">
    <el-row class="main-table-header">
      <el-col :span="18">
        <el-form :inline="true"
                 :model="formInline"
                 class="demo-form-inline">
          <el-form-item label="审批人">
            <el-input v-model="formInline.user"
                      placeholder="审批人"></el-input>
          </el-form-item>
          <el-form-item label="活动区域">
            <el-select v-model="formInline.region"
                       placeholder="活动区域">
              <el-option label="区域一"
                         value="shanghai"></el-option>
              <el-option label="区域二"
                         value="beijing"></el-option>
            </el-select>
          </el-form-item>
          <el-form-item>
            <el-button type="primary"
                       @click="onSubmit">查询</el-button>
          </el-form-item>
        </el-form>
      </el-col>
      <el-col :span="6"
              class="main-table-header-action">
        <el-button @click="addData"
                   type="success">添加</el-button>
      </el-col>
    </el-row>
    <el-row class="main-table-body">
      <el-table :data="tableData4"
                stripe
                style="main-table"
                :height="tableHeight">
        <el-table-column type="selection"
                         width="55">
        </el-table-column>
        <el-table-column fixed
                         sortable
                         prop="date"
                         label="日期"
                         width="150">
        </el-table-column>
        <el-table-column prop="name"
                         sortable
                         label="姓名"
                         width="120">
        </el-table-column>
        <el-table-column prop="province"
                         label="省份"
                         width="120">
        </el-table-column>
        <el-table-column prop="city"
                         label="市区"
                         width="120">
        </el-table-column>
        <el-table-column prop="address"
                         label="地址">
        </el-table-column>
        <el-table-column prop="zip"
                         label="邮编"
                         width="120">
        </el-table-column>
        <el-table-column fixed="right"
                         label="操作"
                         width="120">
          <template slot-scope="scope">
            <el-button @click.native.prevent="deleteRow(scope.$index, tableData4)"
                       type="text"
                       size="small">编辑</el-button>
            <el-button @click.native.prevent="deleteRow(scope.$index, tableData4)"
                       type="text"
                       size="small">
              移除
            </el-button>
          </template>
        </el-table-column>
      </el-table>
    </el-row>
    <el-row class="main-table-footer">
      <el-col :span="12">
        <el-button @click="toggleSelection([tableData3[1], tableData3[2]])"
                   type="danger">删除</el-button>
        <el-button @click="toggleSelection()"
                   type="primary">全部选择</el-button>
      </el-col>
      <el-col :span="12"
              class="main-table-pagination">
        <el-pagination @size-change="handleSizeChange"
                       @current-change="handleCurrentChange"
                       :current-page="currentPage4"
                       :page-sizes="[100, 200, 300, 400]"
                       :page-size="100"
                       layout="total, sizes, prev, pager, next, jumper"
                       :total="400">
        </el-pagination>
      </el-col>
    </el-row>
    <el-dialog title="收货地址"
               :visible.sync="dialogFormVisible"
               width="30%"
               class="main_dialog">
      <el-form :model="form"
               label-width="80px">
        <el-form-item label="活动名称">
          <el-input v-model="form.name"
                    auto-complete="off"></el-input>
        </el-form-item>
        <el-form-item label="活动区域">
          <el-select v-model="form.region"
                     placeholder="请选择活动区域">
            <el-option label="区域一"
                       value="shanghai"></el-option>
            <el-option label="区域二"
                       value="beijing"></el-option>
          </el-select>
        </el-form-item>
      </el-form>
      <div slot="footer"
           class="dialog-footer">
        <el-button @click="dialogFormVisible = false">取 消</el-button>
        <el-button type="primary"
                   @click="dialogFormVisible = false">确 定</el-button>
      </div>
    </el-dialog>
  </div>
</template>

<script>
export default {
  name: 'ZnMain',
  data() {
    return {
      dialogFormVisible: false,
      formInline: {
        user: '',
        region: ''
      },
      form: {
        name: '',
        region: '',
        date1: '',
        date2: '',
        delivery: false,
        type: [],
        resource: '',
        desc: ''
      },
      currentPage1: 5,
      currentPage2: 5,
      currentPage3: 5,
      currentPage4: 4,
      tableHeight: 0,
      tableData4: [
        {
          date: '2016-05-03',
          name: '王小虎',
          province: '上海',
          city: '普陀区',
          address: '上海市普陀区金沙江路 1518 弄',
          zip: 200333
        },
        {
          date: '2016-05-02',
          name: '王小虎',
          province: '上海',
          city: '普陀区',
          address: '上海市普陀区金沙江路 1518 弄',
          zip: 200333
        },
        {
          date: '2016-05-04',
          name: '王小虎',
          province: '上海',
          city: '普陀区',
          address: '上海市普陀区金沙江路 1518 弄',
          zip: 200333
        },
        {
          date: '2016-05-01',
          name: '王小虎',
          province: '上海',
          city: '普陀区',
          address: '上海市普陀区金沙江路 1518 弄',
          zip: 200333
        },
        {
          date: '2016-05-08',
          name: '王小虎',
          province: '上海',
          city: '普陀区',
          address: '上海市普陀区金沙江路 1518 弄',
          zip: 200333
        },
        {
          date: '2016-05-06',
          name: '王小虎',
          province: '上海',
          city: '普陀区',
          address: '上海市普陀区金沙江路 1518 弄',
          zip: 200333
        },
        {
          date: '2016-05-07',
          name: '王小虎',
          province: '上海',
          city: '普陀区',
          address: '上海市普陀区金沙江路 1518 弄',
          zip: 200333
        },
        {
          date: '2016-05-06',
          name: '王小虎',
          province: '上海',
          city: '普陀区',
          address: '上海市普陀区金沙江路 1518 弄',
          zip: 200333
        }
      ]
    }
  },
  mounted() {
    this.$nextTick(() => {
      this.tableHeight = window.innerHeight - 300
    })
  },
  methods: {
    addData() {
      this.dialogFormVisible = true
    },
    onSubmit() {
      console.log('submit!')
    },
    toggleSelection(rows) {
      if (rows) {
        rows.forEach(row => {
          this.$refs.multipleTable.toggleRowSelection(row)
        })
      } else {
        this.$refs.multipleTable.clearSelection()
      }
    },
    handleSelectionChange(val) {
      this.multipleSelection = val
    },
    deleteRow(index, rows) {
      rows.splice(index, 1)
    },
    handleSizeChange(val) {
      console.log(`每页 ${val} 条`)
    },
    handleCurrentChange(val) {
      console.log(`当前页: ${val}`)
    }
  }
}
</script>

<style>
.el-dialog__header {
  background: #409eff;
}
.el-dialog__header * {
  color: #fff !important;
}
.main_dialog {
  text-align: left;
  border: 1px solid #efefef;
}
.main_border {
  background: #fff;
  border: 1px solid #efefef;
  box-shadow: 0px 2px 10px 0px rgba(0, 0, 0, 0.1);
}
.main-table-header,
.main-table-footer {
  margin: 10px;
  padding-left: 15px;
  background: #ffffff;
  height: 40px;
  text-align: left;
}
.main-table-body {
  border-top: 1px solid #efefef;
  padding: 0px;
  margin: 0px;
  background: #409eff;
}
.main-table {
  width: 100%;
}
.main-table-header-action {
  padding-right: 15px;
  text-align: right;
}
.main-table-pagination {
  padding-top: 5px;
  padding-right: 15px;
  text-align: right;
}
div::-webkit-scrollbar {
  /*滚动条整体样式*/
  width: 8px;
  /*高宽分别对应横竖滚动条的尺寸*/
  height: 1px;
}

div::-webkit-scrollbar-thumb {
  /*滚动条里面小方块*/
  border-radius: 10px;
  background-color: rgb(82, 87, 88);
  background-image: -webkit-linear-gradient(
    45deg,
    rgba(102, 175, 233, 0.2) 25%,
    transparent 25%,
    transparent 50%,
    rgba(102, 175, 233, 0.2) 50%,
    rgba(102, 175, 233, 0.2) 75%,
    transparent 75%,
    transparent
  );
}

div::-webkit-scrollbar-track {
  /*滚动条里面轨道*/
  box-shadow: inset 0 0 5px rgba(0, 0, 0, 0.2);
  background: #ededed21;
  border-radius: 10px;
}
</style>
