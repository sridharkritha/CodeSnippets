window.addEventListener('load', function() {

	var withoutArg = null;
	var withArg = null;
	var withCtxArg = [];
	var index = 0;

	function registerBook(obj)
	{
		if(obj.callback_without_arg)
			withoutArg = obj.callback_without_arg;
		if(obj.callback_with_arg)
			withArg = obj.callback_with_arg;
		if(obj.callback_with_arg_with_context)
			withCtxArg[index++] = obj.callback_with_arg_with_context;
	}

	function print() {
		setTimeout(function() {
			withoutArg(); // directly calls 'function noArgmentedFun(value) { }'

			withArg(999); // calls: 'argmentedFun(value)' inside function wrapper;
						  // NOT directly calls the definition 'function argmentedFun(value) { }'

			for(var i = index -1; i>= 0; --i) {
				withCtxArg[i](10); // calls: argmentedFunWithContext.call(contextObject, value) inside function wrapper; 
									// which inturns call the definition 'function argmentedFunWithContext(value) { }'
									// NOT directly calls 'function argmentedFunWithContext(value) { }'
			}
		}, 5000);
	}

	function noArgmentedFun() {
		console.log("noArgmentedFun()");
	}

	function argmentedFun(value) {
		console.log(value);
	}

	function argmentedFunWithContext(value) {
		console.log(this.abc * value); // NOTE: this object
	}


	function fun()	{
		registerBook({
						"callback_without_arg": 
												noArgmentedFun, // calledby: NOTHING
						"callback_with_arg": function(value) {
												argmentedFun(value); // calledby: withArg(999);, calls: function argmentedFun(value) { } 
												}
					 });


		var something = [];

		for(var index = 0; index < 6; ++index) {
				something[index] = { }; // creates DIFFERENT this objects
				something[index].abc = index;
				registerBook({ "callback_with_arg_with_context": 
					(function(contextObject) {  // object as context / this
							return function(value) {
											argmentedFunWithContext.call(contextObject, value);
										};
					}.bind(this))(something[index]) // IIF- passing different 'this' object from something[index]
				});
		}

					 print();

					//  for(var index = 0; index < 6; ++index)
					//  {
					// 	 something[index] = { }; // object as context / this
					// 	 something[index].abc = index;
					// 	 registerBook({ "callback_with_arg_with_context": 
					// 		 (function(contextObject) {  // object as context / this
					// 			 return function(value) { 
					// 				argmentedFunWithContext.call(contextObject, value);
					// 					 }.bind(this);
					// 		 }.bind(this))(something[index])
					// 	 });
					//  }
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
