function myFunction() 
{ 
    var name, age; 
    name = document.getElementById("inputName");
    age  = parseInt(document.getElementById("inputAge"));
    document.getElementById("displayElement").innerHTML = name +" " + age; 
}