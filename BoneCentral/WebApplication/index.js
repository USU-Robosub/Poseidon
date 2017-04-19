var express         	= require('express');
var bodyParser      	= require('body-parser');
var routes              = require('./routes.js');
var messenger           = require('./messenger.js');
var port                = 80;
var app             	= express();

app.use('/', express.static('static'));
app.use(bodyParser.json());
routes(app, messenger);

app.listen(port, function () {
  console.log('Web app listening on port 80!');
});
