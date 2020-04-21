const { Api, JsonRpc } = require("eosjs");
const fetch = require("node-fetch");
const { JsSignatureProvider } = require('eosjs/dist/eosjs-jssig');
const { TextEncoder, TextDecoder } = require('util');

// signing wallet
const defaultPrivateKey = "5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3";
const signatureProvider = new JsSignatureProvider([defaultPrivateKey]);

// latest eosjs
const endpoint = "http://localhost:8888";
const rpc = new JsonRpc(endpoint, { fetch });
const api = new Api({ rpc, signatureProvider, textDecoder: new TextDecoder(), textEncoder: new TextEncoder() });

// main
(async () => {
    const account = "pingpong.sx";
    const authorization = [{ actor: 'myaccount', permission: 'active' }];

    // ping action
    const ping = {
        account,
        name: 'ping',
        authorization,
        data: {
            uid: 250,
            type: "mytype"
        },
    }
    // pong action
    const pong = {
        account,
        name: 'pong',
        authorization,
        data: {
            account: "myaccount",
            uid: 250,
        },
    }
    const options = {
        blocksBehind: 3,
        expireSeconds: 30,
    }
    const result = await api.transact({ actions: [ping, pong] }, options);
    console.dir(result);
})();

