window.addEventListener('load', function() {
	var a = [10, 20, 30];

	function fun()	{
		for(var i = 0; i < 3; ++i)
		{

			// Solution 2: Wrap up using 1. Anonymous function and 2. Argument passing
			// (function() { })(); // Anonymous function
			(function(param) { 
				setTimeout(function() {
					console.log(a[param]); // 10 20 30
				}.bind(this), 100);
			})(i);
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
