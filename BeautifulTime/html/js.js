var zones = ["jp","kumamoto","tokyo","nagoya","fukui","tochigi","okinawa","gunma","akita","kagoshima","niigata","saitama","fukuoka","kanazawa","kyoto"];
var size = zones.length;
var time = "";
var time_num_only = "";
var zone = "jp";

function clicked(){
    zone = getNextZone();
    updateImage(zone,t);
}

function getTime(){
    var date = new Date();
    var hour = date.getHours();
    var minute = date.getMinutes();
    hour = hour<10?"0"+hour:hour;
    minute = minute<10?"0"+minute:minute;
    var current = hour+""+minute;
    if(time_num_only!=current){
      time = hour+":"+minute;
    }
    return current;
}

function getRandomZone(){
    var i = Math.floor(Math.random()*size);
    var z = zones[i];
    return z;
}

function getNextZone(){
    var i = zones.indexOf(zone);
    i = (i+1)%size;
    return zones[i];
}

function updateImage(z, t){
    var url = "http://www.bijint.com/"+z+"/tokei_images/"+t+".jpg";
    document.body.style.backgroundImage="url('"+url+"')";
    document.body.style.backgroundRepeat="no-repeat";
    document.getElementById("time").innerHTML = time;
}

function refresh(){
    var t=getTime()+"";
    if(time_num_only!=t){
        var str = time_num_only+"";
        str = str.substring(str.length-1);
        if(str=="1"||str=="6"){
            zone = getRandomZone();
        }

        updateImage(zone,t);
    }
}

setInterval(refresh, 1000);
