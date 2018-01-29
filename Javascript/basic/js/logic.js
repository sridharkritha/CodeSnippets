window.addEventListener('load', function() {
    function myFunction() 
    { 
        var name, age; 
        name = document.getElementById("inputName").value;
        age  = parseInt(document.getElementById("inputAge").value);
        document.getElementById("displayElement").innerHTML = name +" " + age; 
    }
}) // window.addEventListener('load', function() {
