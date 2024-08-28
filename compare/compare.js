const fs = require("fs");
const args = process.argv;
const filePath = args.at(-1);
const file = fs.readFileSync(filePath).toString();
const tables = file.split(";;\n").map((t) => t.split("{}"));
tables.pop();
const len = tables.length;
// console.log(tables);
const result = true;

function compare() {
  for (let i = len - 1; i > 0; i--) {
    const table1 = tables[i];
    const table2 = tables[i - 1];
    let table2_len = table2.length;
    if (table2[table2_len - 1] == "") {
      table2.pop();
      table2_len--;
    }
    for (let j = 0; j < table2_len; j++) {
      // console.log(table1[j], table2[j]);
      if (table1[j] !== table2[j]) {
        // console.dir(table1.splice(513));
        // console.dir(table2.splice(513));
        console.log("wrong on this tables", "on", j, table1[j], "idx:", i);
        return;
      }
    }
  }
}

compare();
