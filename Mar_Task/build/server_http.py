from flask import Flask, request, jsonify
import ctypes

# Загрузка C++ библиотеки
lib_path = '/home/sadrudin/206-Sadrud/Mar_Task/build/libmy_algorithm.so'
lib = ctypes.CDLL(lib_path)
lib.findContour.argtypes = [ctypes.c_char_p]
lib.findContour.restype = ctypes.c_char_p

app = Flask(__name__)

@app.route('/process', methods=['POST'])
def process():
    data = request.json.get('data')
    result = lib.findContour(data.encode('utf-8')).decode('utf-8')
    return jsonify({"result": result})

if __name__ == "__main__":
    app.run(host='127.0.0.1', port=5000)
