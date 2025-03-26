import matplotlib.pyplot as plt
from shapely.geometry import Polygon, MultiPolygon
import numpy as np
import os
import glob
from pathlib import Path

INPUT_FOLDER = "input"

def load_data(filename):
    """Загружает рёбра из файла."""
    rectangles = []
    edges = []
    try:
        with open(filename, 'r') as f:
            for line in f:
                parts = list(map(float, line.strip().split()))
                if len(parts) == 8:  # Прямоугольник
                        rectangles.append([(parts[i*2], parts[i*2+1]) for i in range(4)])
                elif len(parts) == 4:  # Ребро контура
                    edges.append(((parts[0], parts[1]), (parts[2], parts[3])))
    except Exception as e: 
        print(f"Ошибка при загрузке {filename}: {e}")
    return rectangles, edges

def save_visualization(input_file, output_dir="output"):
    rectangles, edges = load_data(input_file)
    if not rectangles and not edges:
        print(f"Файл {filepath} не содержит корректных данных.")
        return
    
    os.makedirs(output_dir, exist_ok=True)
    plt.figure(figsize=(12, 6))

    # Рисуем прямоугольники
    plt.subplot(1, 2, 1)
    for rect in rectangles:
    # Замыкаем прямоугольник (возвращаемся к первой точке)
        x = [p[0] for p in rect] + [rect[0][0]]
        y = [p[1] for p in rect] + [rect[0][1]]
        plt.plot(x, y, 'b-', linewidth=1)
        plt.fill(x, y, 'b', alpha=0.1)
    plt.title("Исходные прямоугольники")
    plt.grid(True)
    plt.axis('equal')

    # Рисуем каждое ребро
    plt.subplot(1, 2, 2)
    for (p1, p2) in edges:
        plt.plot([p1[0], p2[0]], [p1[1], p2[1]], 'r-', linewidth=2)
    plt.title("Контур объединения")
    plt.grid(True)
    plt.axis('equal')
        
    output_file = f"{output_dir}/{Path(input_file).stem}.png"
    plt.tight_layout()
    plt.savefig(output_file)
    plt.close()
    print(f"Сохранено: {output_file}")

if __name__ == "__main__":
    search_path = os.path.join(INPUT_FOLDER, "*.txt")
    files = glob.glob(search_path)
    if not files:
        print("Ошибка: Не найдены .txt файлы с рёбрами!")
    else:
        print("Найдены файлы:")
        for file in files:
            print(f"  - {file}")
        for file in files:
            print(f"Обработка файла {file}")
            save_visualization(file)
        print("\nВсе файлы обработаны. Результаты в папке 'output'")

