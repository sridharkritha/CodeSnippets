// function myFunction() 
// { 
//     var name, age; 
//     name = document.getElementById("inputName").value;
//     age  = parseInt(document.getElementById("inputAge").value);
//     document.getElementById("displayElement").innerHTML = name +" " + age; 
// }

window.addEventListener('load', function() {

	function getComputedSize()
	{
		var bodyWidth = parseFloat(getComputedStyle(document.body).width);
		var bodyHeight = parseFloat(getComputedStyle(document.body).height);
		return {width: bodyWidth, height: bodyHeight};
	}

	console.log(getComputedSize());

	// object: the element or window object
	// type: resize, scroll (event type)
	// callback: the function reference
	var addEvent = function(object, type, callback) {
		if (object == null || typeof(object) == 'undefined') return;
		if (object.addEventListener) {
			object.addEventListener(type, callback, false);
		} else if (object.attachEvent) {
			object.attachEvent("on" + type, callback);
		} else {
			object["on"+type] = callback;
		}
	};

	addEvent(window, "resize", onBrowserWindowResize);

	function onBrowserWindowResize(event) {
		console.log('resized: ' + event.target.screen.width + ' x ' + event.target.screen.height);

		resetViewArea(event.target.screen.width, event.target.screen.height);
	}

	function resetViewArea(screenWidth, screenHeight) {
		var head = document.head || document.getElementsByTagName('head')[0],
		style = document.createElement('style');
		head.appendChild(style);
	
		// var css = '.renderer-view { background: red; }';

		var css = `#renderer-view { width: ${screenWidth}px; height: ${screenHeight}px; }`;
	
		style.type = 'text/css';
		if (style.styleSheet)
		{  
			style.styleSheet.cssText = css; // This is required for IE8 and below.
		} 
		else {
			style.appendChild(document.createTextNode(css));
		}
	}





	// var head = document.head || document.getElementsByTagName('head')[0],
	// style = document.createElement('style');
	// head.appendChild(style);

	// var css = 'h1 { background: red; }';

	// style.type = 'text/css';
	// if (style.styleSheet)
	// {  
	// 	style.styleSheet.cssText = css; // This is required for IE8 and below.
	// } 
	// else {
	// 	style.appendChild(document.createTextNode(css));
	// }

}); // window.addEventListener('load', function() {


