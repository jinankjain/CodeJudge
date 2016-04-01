(function() {

  var mysql = require('mysql');
 
  var connection = mysql.createConnection(
      {
        host     : 'localhost',
        user     : 'root',
        password : 'kritikajain',
        database : 'codejudge',
      }
  );
   
  connection.connect();

  var parse = function(data) {
    var json = JSON.parse(data);
    return json;
  };

  var reportCompileFail = function(id, msg) {
    
    console.log(msg);
    var queryString = 'UPDATE judge_solution SET status=1 WHERE id='+id;
    connection.query(queryString, function(err, rows, fields) {
      if (err) throw err;
    });
  };

  var reportRunFail = function(id, msg) {
    console.log(msg);
    var queryString = 'UPDATE judge_solution SET status=2 WHERE id='+id;
    connection.query(queryString, function(err, rows, fields) {
      if (err) throw err;
    });
  };

  var reportTLE = function(id) {
    console.log(msg);
    var queryString = 'UPDATE judge_solution SET status=3 WHERE id='+id;
    connection.query(queryString, function(err, rows, fields) {
      if (err) throw err;
    });
    // TLE reporting code here
  };

  var reportResult = function(id, msg) {
    console.log(msg);
    
    if(msg==1)
    {
        var queryString = 'UPDATE judge_solution SET status=4 WHERE id='+id;
        connection.query(queryString, function(err, rows, fields) {
            if (err) throw err;
        });
    }
    else
    {
        var queryString = 'UPDATE judge_solution SET status=5 WHERE id='+id;
        connection.query(queryString, function(err, rows, fields) {
            if (err) throw err;
        });
    }
    
    // code that handles the result of the code
    // do whatever you want to write to the db here
  }

  module.exports.parse = parse;
  module.exports.reportCompileFail = reportCompileFail;
  module.exports.reportRunFail = reportRunFail;
  module.exports.reportResult = reportResult;
  module.exports.reportTLE = reportTLE;
})();