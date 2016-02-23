$(document).ready(function(){


	var heightUpdateFunction = function() {

	        // http://stackoverflow.com/questions/11584061/
	        var newHeight =
	                  editor.getSession().getScreenLength()
	                  * editor.renderer.lineHeight
	                  + editor.renderer.scrollBar.getWidth() + 410;

	        $('#editor').height(newHeight.toString() + "px");
	        $('#editor-section').height(newHeight.toString() + "px");

	        // This call is required for the editor to fix all of
	        // its inner structure for adapting to a change in size
	        editor.resize();
	};

	var indentSpaces = 4;

	function readCookie(name) {
	    var nameEQ = name + "=";
	    var ca = document.cookie.split(';');
	    for (var i = 0; i < ca.length; i++) {
	        var c = ca[i];
	        while (c.charAt(0) == ' ') c = c.substring(1, c.length);
	        if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length, c.length);
	    }
	    return null;
	}

	var editor = ace.edit("editor");
	ace.require("document");
	// var doc = new Document(editor.getValue());

	editor.setTheme("ace/theme/chrome");
	editor.session.setMode("ace/mode/c_cpp");
	editor.getSession()
	    .setTabSize(indentSpaces);
	editorContent = editor.getValue();
	editor.setFontSize(13);
	editor.setOptions({
	    useWrapMode: true
	    , showPrintMargin: false
	    , enableBasicAutocompletion: true
	    , enableSnippets: true
	    , enableLiveAutocompletion: true
	});

	var StatusBar = ace.require("ace/ext/statusbar")
	    .StatusBar;
	var statusBar = new StatusBar(editor, document.getElementById("editor-statusbar"));

	heightUpdateFunction();
});