const path=require('path')
const grpc=require('@grpc/grpc-js')
const protolodar=require('@grpc/proto-loader')

const proto_path=path.join(__dirname,'message.proto')
const packgafin=protolodar.loadSync(proto_path,
    {keepCase:true,longs:String,enums:String,defaults:true,oneofs:true})


const protoDescriptor=grpc.loadPackageDefinition(packgafin);
const message_proto=protoDescriptor.message
module.exports=message_proto