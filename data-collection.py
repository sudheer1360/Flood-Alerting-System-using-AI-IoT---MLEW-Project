import serial
import pandas as pd

ser=serial.Serial('COM5',115200,timeout=0.5)

count=0
dataset=[]
while True:
    try:
        if ser.inWaiting()>0:
            data=ser.readline()
            data=data.decode('utf-8')
            if data.startswith('#'):
                data=data.split(',')
                dummy=[int(data[1]),data[2]]
                count+=1
                dataset.append(dummy)
                if count==50:
                    df=pd.DataFrame(dataset)
                    df.to_csv('iotdata.csv')
                    count=0
            print(dataset)
    except:
        print('Data Configuration Failed')
