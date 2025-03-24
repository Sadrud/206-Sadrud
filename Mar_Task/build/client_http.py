import requests

data = {"data": "hello, server!"}
response = requests.post('http://127.0.0.1:5000/process', json=data)
print(response.json())
