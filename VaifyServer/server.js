const grpc=require('@grpc/grpc-js')
const const_module=require('./const')
const message_proto=require('./proto')
const {v4:uuidv4} =require('uuid')
const emailModule=require('./email')
const redism=require('./redis')

async function GetVarifyCode(call, callback) {
    console.log("email is ", call.request.email)
    try{
        let res_v=await redism.Getkey(const_module.code_prefix+call.request.email);
        if(res_v==null){

        }
        let uniqueId=res_v
            if(res_v==null){
            uniqueId = uuidv4();
            if(uniqueId.length>4){
                console.log("uniqueId is 123", uniqueId)
                uniqueId=uniqueId.substring(0, 4);
            }
            
        let setexpire=await redism.setandexpiry(const_module.code_prefix+call.request.email,uniqueId,60);
            if(!setexpire){
            callback(null, {email: call.request.email,
            error:const_module.Errors.Exception});
            return;
            }
            
        }

            if(uniqueId.length>4){
                console.log("uniqueId is 123", uniqueId)
                uniqueId=uniqueId.substring(0, 4);
            }
        console.log("uniqueId is ", uniqueId)
        let text_str =  '您的验证码为'+ uniqueId +'请三分钟内完成注册'
        //发送邮件
        let mailOptions = {
            from: '3085159655@qq.com',
            to: call.request.email,
            subject: '验证码',
            text: text_str,
        };
        let send_res = await emailModule.SendMail(mailOptions);
        console.log("send res is ", send_res)
        callback(null, { email:  call.request.email,
            error:const_module.Errors.Success
        });   
    }catch(error){
        console.log("catch error is ", error)
        callback(null, { email:  call.request.email,
            error:const_module.Errors.Exception
        }); 
    }
}
function main() {
    var server = new grpc.Server()
    server.addService(message_proto.VarifyService.service, { GetVarifyCode: GetVarifyCode })
    server.bindAsync('0.0.0.0:50051', grpc.ServerCredentials.createInsecure(), () => {
        console.log('grpc server started')        
    })
}
main()