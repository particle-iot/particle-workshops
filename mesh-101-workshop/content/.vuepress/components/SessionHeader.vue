<template>
  <div class="sbox-container">
    <div class="sbox-table">
      <div class="sbox-row">
        <div class="sbox-header">Goal </div>
        <div class="sbox-content">{{goal_}}</div>
      </div>
      <div class="sbox-row">
        <div class="sbox-header"> Time </div>
        <div class="sbox-content"> {{time_}} min </div>
      </div>
      <div class="sbox-row">
        <div class="sbox-header"> Tools </div>
        <div class="sbox-content">
          <ul>
            <li v-for="t in tools_">{{t}}</li>
          </ul>
        </div>
      </div>
    </div>
  </div>

    <!--table>
      <tr>
        <td class="head">Goal</td>
        <td> {{goal_}}</td>
      </tr>
      <tr>
        <td class="head">Time</td>
        <td> {{time_}}min </td>
      </tr>
      <tr>
        <td class="head">Tools</td>
        <td>
          <ul>
            <li v-for="t in tools_">{{t}}</li>
          </ul>
        </td>
      </tr>
    </table-->

</template>
<script>
export default {
  props: ['goal', 'time', 'tools'],
  data() {
    // Same names will generate general Vue warning.
    return {
      goal_: this.goal,
      time_: this.time,
      tools_: this.tools
    }
  }
}
</script>

<style scoped>
.sbox-container {
  display: block;
  background-color: #f3f5f7;
  border-left: solid 0.5rem #031E41;
  margin: 1rem 0;
  padding: 0.1rem 1.5rem 
}

.sbox-table {
  display: table;
  margin-block-start: .9rem;
  margin-block-end: .7rem;
}

.sbox-row {
  display: table-row;
  background-color: #f3f5f7;
}

.sbox-content, .sbox-header {
  display: table-cell;
  padding: .3rem 0;
}

.sbox-header {
  font-weight: 600;
  padding-right: 20px;
  text-align: right;
}

ul {
  margin-top: 0;
  margin-bottom: 0;
}

li {
  margin: -5px 0;
}
</style>