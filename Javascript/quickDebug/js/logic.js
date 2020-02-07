window.addEventListener('load', function() {
	var listFunc = null;
	function registerBook(obj)
	{
		listFunc = obj.valueCallback;
		listFunc(5);
	}

	function callback(value)
	{
		console.log(value);
	}

	function fun()	{
		registerBook({valueCallback: function(value) {callback(value);}.bind(this)});

		for(var index = 0; index < 6; ++index)
		{
			something[index] = { }; // object as context / this
			something[index].abc = 4;
			registerBook({ valueCallback: 
				(function(contextObject) {  // object as context / this
					return function(value) { 
						callback.call(contextObject, value);
							}.bind(this);
				}.bind(this))(something[index])
			
			});
}



	}






















	// button
	document.getElementById('btnIdPrevious').onclick = function () { 
		fun();
		/////////////////////////////////////////////////
		var name, age; 
		name = document.getElementById("inputName").value;
		age  = parseInt(document.getElementById("inputAge").value);
		document.getElementById("displayElement").innerHTML = name +" " + age; 
	};
}); // window.addEventListener('load', function() {
