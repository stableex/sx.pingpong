const { JsonRpc } = require("eosjs");
const fetch = require("node-fetch");

// latest eosjs
const endpoint = "http://localhost:8888";
const rpc = new JsonRpc(endpoint, { fetch });

// main
(async () => {
    // multi-index
    const code = "pingpong.sx";
    const scope = "pingpong.sx";
    const table = "pings";

    // fetch data
    const results = await rpc.get_table_rows({json: true, code, scope, table})

    // log data
    for (const row of results.rows) {
        console.log(row)
    }
})();