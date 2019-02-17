const express = require("express");
const mysql = require("mysql");
const cors = require("cors");
const bodyParser = require("body-parser");
const app = express();

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
app.use(cors);

const con = mysql.createConnection({
    host: "localhost",
    port: 3306,
    user: "root",
    password: "password",
    database: "pulseScan"
})

app.get("/users/:name", function(req, res) {
    const name = req.params.name;
    con.query("SELECT * FROM pulseScan.users WHERE name = '" + name + "'", function(err, result) {
        console.log(result);
        return res.json(result);
    })
})

app.listen(5000, () => {
    console.log('Go to http://localhost:5000/users to see posts');
   });