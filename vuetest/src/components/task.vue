<template>
    <div>
        <h1>{{msg}}</h1>
    </div>
    <div id="field">
        <label v-for="label in options" :key="label">
        <input type="radio" v-model="current" v-bind:value="label.value">{{ label.label }}</label>
        
        <table>
        <thead>
            <tr>
                <!--<th class="id">ID</th>-->
                <th class="comment">タスク名</th>
                <th class="limit">期限</th>
                <th class="state">状態</th>
                <th class="button">-</th>
            </tr>
        </thead>
        <tr v-for="task in Tasker" :key="task.id">
            <!--<th>{{memo.id}}</th>-->
            <th>{{task.title}}</th>
            <td>{{task.date}}</td>
            <td class="state"><button @click="state(task)">{{labels[task.state]}}</button></td>
            <td class="button"><button @click="check(task)">削除</button></td>
        </tr>
        </table>
    </div>
    <br><br>
    <button @click="hsort()">日付ソート</button><br>
    <br>
    <form>
        <input type="text" v-model="addText"><br>
        <input type="date" v-model="addDate"><br>
    </form>
    <button @click="add">追加</button>
</template>

<script>
export default {
    name: 'Task',
    props: {
        msg: String
    },
    data() {
        return {
            task:[],
            options:[  //タスクの状態管理用データ
                { value: -1, label:'すべて'},
                { value: 0, label:'作業中'},
                { value:1, label:'完了'},
                { value: 2, label:'作業前'}
            ],
            current: -1,
            Today: ''//日付周りに使用予定が断念
      }
      
  },
    computed: {
        Tasker: function () {//タスクの状態による絞り込み機能
            return this.task.filter(function (el) {
            return this.current < 0 ? true : this.current === el.state}, this)
        },
        labels() {//タスクの状態を数字から文字へ変換
            return this.options.reduce(function (a, b) {
            return Object.assign(a, { [b.value]: b.label })}, {})
            // {0: '作業中', 1: '完了', 2: '作業前'}
        },
        /*setToday: function(){ //本来ならここでシステム上の日付を取得し、タスク側の期限と比較し、期限切れのタグ付けを行う（失敗）
            var kyou = new Date();
            var year = kyou.getFullYear();
            var month = kyou.getMonth();
            var day = kyou.getDate();
            this.Today.push({
                year: this.year,
                month: this.month,
                day: this.day
            })
        }*/
    },
    mounted() {//ローカルストレージから読み込み
      if(localStorage.getItem('task')) {
          try {
              this.task = JSON.parse(localStorage.getItem('task'));
          } catch(e) {
              localStorage.removeItem('task');
          }
      }
  },
  methods: {
      add() {//追加実行時入力された情報を配列に追加
          this.task.push({
              //id: this.memo.uid++, //id処理失敗したため、コメントアウト
              title: this.addText,
              state: 2, //初期数値は作業前を表す2
              date: this.addDate,
          });
          this.addText ="";
          this.addURL = "";
          this.addDate ="";
          this.save();
      },
      check(x) {//削除前の確認ポップアップ、ok選択時のみremove関数を実行
          var result = confirm("削除は取り消せません、よろしいですか");
          if(result) {
              this.remove(x);
          }
      },
      remove(x) {//remove実行時spliceで削除
          alert("削除しました");
          this.task.splice(x,1);
          this.save();
      },
      state(task) {//タスクの状態変化
          if(task.state ==2) {//初期設定が2なので一度目は0に
              task.state =0
          }else {//作業中（0）と完了（1）の切り替え
              task.state = task.state ? 0 : 1
          } 
          this.save();
      },
      save() {//各メソッド実行後ローカルに保存
          let parsed = JSON.stringify(this.task);
          localStorage.setItem('task', parsed);
      },
      hsort() {//登録タスク内の日付からソート
          this.task.sort(function(a,b){
              if(a.date < b.date) {
                  return -1;
              }else {
                  return 1;
              }
          });
      }
  }
}
</script>
<style>
/* {
  box-sizing: border-box;
}*/
#app {
  max-width: 640px;
  margin: auto;
}
#field{
    display: inline-block;
    /*margin: 0 auto;*/
}
table {
  width: 100%;
  border-collapse: collapse;
}
thead th {
  border-bottom: 2px solid #009944; /*#d31c4a */
  color: #009944;
}
tr {
    border-bottom: 1px solid #009922;
}
th,
th {
  padding: 0 8px;
  line-height: 40px;
}
thead th.id {
  width: 50px;
}
thead th.state {
  width: 100px;
}
thead th.button {
  width: 60px;
}
tbody td.button, tbody td.state {
  text-align: center;
}
tbody tr td,
tbody tr th {
  border-bottom: 1px solid #ccc;
  transition: all 0.4s;
}

button {
  border: none;
  border-radius: 15px;
  line-height: 24px;
  padding: 0 8px;
  background: #009944;
  color: #fff;
  cursor: pointer;
}
input {
    margin-bottom: 5px;
}


</style>