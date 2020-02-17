window.addEventListener('load', function() {
	function fun()	{
//******************************************************************* thisSridhar (context) *************************************************************************************
		var thisSridhar = { }; // 'this' object named as sridhar
		thisSridhar.name = "thisSridhar";
		
		thisSridhar.noArgmentedFun = function() {
			console.log("noArgmentedFun()");
		};

		thisSridhar.argmentedFun = function(value) {
			console.log(value);
		};

		thisSridhar.argmentedFunWithContext = function(value) {
			console.log(this.abc * value); // NOTE: this object
		};

		thisSridhar.someFunction = function () 
		{
			thisKavitha.registerBook({
										"callback_without_arg":
																this.noArgmentedFun, // calledby: NOTHING
										"callback_with_arg": 
															function(value) {
																this.argmentedFun(value); // calledby: thisKavitha.withArg(999); BUT 'this === thisSridhar' NOT 'thisKavitha' bcos bind.
																						  // calls: thisSridhar.argmentedFun = function(value) { { } 
															}.bind(this) // bind - MUST. NOTE: Here 'this == thisSridhar' 
									});

			this.thisSridharSubObjects = []; // collection of 'this' objects inside an object

			for(var index = 0; index < 1; ++index) 
			{
				this.thisSridharSubObjects[index] = { }; // creates DIFFERENT 'this' objects
				this.thisSridharSubObjects[index].name = "thisSridharSubObjects_"+index;
				this.thisSridharSubObjects[index].abc = index; // this === thisSridhar, bcos caller is 'thisSridhar.someFunction();'
				
				thisKavitha.registerBook({ 
											"callback_with_arg_with_context": 
														(function(contextObject) {  // object as context / this
																return function(value) {
																	 			// 'this == thisSridhar' and 'contextObject == thisSridharSubObjects_1'
																				this.argmentedFunWithContext.call(contextObject, value);
																		}.bind(this); // bind - MUST. NOTE: Here 'this == thisSridhar'
														}.bind(this))(this.thisSridharSubObjects[index]) // IIF- passing different 'this' object from thisSridharSubObjects[index]
										});
			}

			thisKavitha.print();
	};

//******************************************************************* thisKavitha (context) *************************************************************************************
	var thisKavitha = { };
	thisKavitha.name = "thisKavitha";
	thisKavitha.index = 0;
	thisKavitha.withCtxArg = [];

	thisKavitha.registerBook = function(obj) {
		if(obj.callback_without_arg)
			thisKavitha.withoutArg = obj.callback_without_arg;
		if(obj.callback_with_arg)
			this.withArg = obj.callback_with_arg;
		if(obj.callback_with_arg_with_context)
			this.withCtxArg[thisKavitha.index++] = obj.callback_with_arg_with_context;
	};

	thisKavitha.print = function() {
		setTimeout(function() {
				this.withoutArg();			// directly calls 'thisSridhar.noArgmentedFun = function() { }'

				thisKavitha.withArg(999);	// calls: 'this.argmentedFun(value);' inside the function wrapper;
											// NOT directly calls the definition 'thisSridhar.argmentedFun = function(value) { }'

				for(var i = this.index -1; i>= 0; --i) {
					this.withCtxArg[i](10); // calls: this.argmentedFunWithContext.call(contextObject, value) inside function wrapper; 
											// which in turns call the definition 'thisSridhar.argmentedFunWithContext = function(value)  { }'
											// NOT directly calls 'thisSridhar.argmentedFunWithContext = function(value)  { }'
			}
		}.bind(thisKavitha), 1000);
	};



	//////////////////////////////////////
	thisSridhar.someFunction();
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
