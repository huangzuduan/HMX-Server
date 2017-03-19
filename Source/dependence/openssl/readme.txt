生成原始私密 
openssl genrsa -out rsa_private_key.pem 1024

生成公钥
openssl rsa -in private_key.pem -pubout -out rsa_public_key.crt

将原始私钥转为pkcs#8格式
openssl pkcs8 -topk8 -inform PEM -in rsa_private_key.pem -outform PEM -nocrypt[ -out rsa_private_key.pem]

将pkcs#8格式转为原始格式
openssl rsa -in rsa_private_key.pem -out rsa_private_key.pem