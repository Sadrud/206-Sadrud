from flask import Flask, request, jsonify
import ctypes

# Загрузка C++ библиотеки
lib = ctypes.CDLL('./libmy_algorithm.so')
lib.process_data.argtypes = [ctypes.c_char_p]
lib.process_data.restype = ctypes.c_char_p

app = Flask(__name__)

@app.route('/process', methods=['POST'])
def process():
    data = request.json.get('data')
    result = lib.process_data(data.encode('utf-8')).decode('utf-8')
    return jsonify({"result": result})

if __name__ == "__main__":
    app.run(host='127.0.0.1', port=5000)
