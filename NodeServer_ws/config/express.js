const express = require('express')
const ejs = require('ejs');
const path = require('path');

module.exports.init = function(app)
{

    app.use(express.static('public'));
    app.set('views', path.join(__dirname, '../views'));
    app.set('view engine', 'ejs');

    let ejsOptions = {outputFunctionName: 'echo'};
    app.engine('ejs', (path, data, cb) => {
        ejs.renderFile(path, data, ejsOptions, cb);
    });
}