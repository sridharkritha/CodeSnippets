window.addEventListener('load', function() {
	function fun()	{
		var a = [10, 20, 30];

		for(var i = 0; i < 3; ++i)
        {
			// Solution 3: IIF and Argument Passing
			setTimeout(function(k) {
				console.log(a[k]); // 10 20 30
			}.bind(this, i), 1000);
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
