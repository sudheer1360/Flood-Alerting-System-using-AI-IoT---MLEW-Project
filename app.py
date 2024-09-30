from flask import Flask,request
import pickle

status=''

with open('model.pkl','rb') as model:
    ai=pickle.load(model)

app=Flask(__name__)

@app.route('/')
def home():
    return 'API Server Running'

@app.route('/predict',methods=['GET'])
def predict():
    global status
    rainfall=int(request.args.get('rainfall'))
    data=[[rainfall]]
    result=ai.predict(data)[0]
    status=result
    return result

@app.route('/status',methods=['GET','POST'])
def getStatus():
    global status
    return status

if __name__=="__main__":
    app.run(
        host='0.0.0.0',
        port=2000
    )