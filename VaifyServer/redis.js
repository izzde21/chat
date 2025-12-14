const con_const=require('./config')
const rdies_c=require("ioredis")


const ReideCil=new rdies_c({

    host:con_const.redis_host,
    port:con_const.redis_port,
    password:con_const.redis_passwd
})


ReideCil.on("error",function(err){
    console.log("连接失败");
    ReideCil.quit();
})


async function Getkey(key){
    try{
    const sult=await ReideCil.get(key);
    if(sult===null){
        console.log("get失败");
        return null
    }
    return sult;
    }catch(err){
        console.log("get失败");
        return null;
    }
}

async function keyexists(key){

    try{
    const sult=await ReideCil.exists(key);
    if(sult===null){
        console.log("不存在");
        return null
    }
    return true;
    }catch(err){
        console.log("不存在");
        return null
    }

}

async function setandexpiry(key,value,exptime){
    try{
        await ReideCil.set(key,value);
        await ReideCil.expire(key,exptime);
        return true;
    }catch(err){
        console.log("setandexpiry error");
        return false;
    }
}



function quit(){
    ReideCil,quit();
}


module.exports={Getkey,setandexpiry,keyexists,quit}