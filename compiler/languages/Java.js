(function(filename, counter) {
  var getCompileScript = function(filename, counter) {
    var script = "cd stage/" + counter + "\n"
               + "javac -nowarn " + filename + " 2>err.txt\n"
               + "exit 0";
    return script;
  };

  var getRunScript = function(filename, time, counter) {
    var dot = filename.lastIndexOf('.');
    var className = filename.substring(0, dot);
    var script = "cd stage/" + counter + "\n"
               + "ulimit -Sv 50000000\n"
               + "ulimit -St " + time + "\n"
               + (config.useFakeChroot ? "fakechroot" : "")
               + " java " + className + " <in.txt 1>tmp.txt 2>err.txt\n"
               + "exit 0";
    return script;
  };

  module.exports.getCompileScript = getCompileScript;
  module.exports.getRunScript = getRunScript;
})();
