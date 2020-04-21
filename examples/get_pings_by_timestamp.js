const { JsonRpc } = require("eosjs");
const fetch = require("node-fetch");

// latest eosjs
const endpoint = "http://localhost:8888";
const rpc = new JsonRpc(endpoint, { fetch });

// main
(async () => {
    // variables
    const code = "pingpong.sx";
    const scope = "pingpong.sx";
    const table = "pings";

    // secondary multi-index
    const limit = 5;
    const reverse = true;
    const index_position = 3; // multi-index (2 = type, 3 = timestamp)
    const key_type = "i64";

    // fetch data
    const results = await rpc.get_table_rows({json: true, code, scope, table, index_position, key_type, reverse, limit})

    // log data
    for (const row of results.rows) {
        console.log(row)
    }
})();