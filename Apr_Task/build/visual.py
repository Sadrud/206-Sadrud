import os
import numpy as np
import matplotlib.pyplot as plt
import networkx as nx
from matplotlib.collections import LineCollection

def visualize_graph_with_eulerian_path(input_dir, output_dir):
    # Создаем выходную папку для изображений, если ее нет
    os.makedirs('visualizations', exist_ok=True)
    
    # Проходим по всем файлам во входной папке
    for filename in os.listdir(input_dir):
        if not filename.endswith('.txt'):
            continue
            
        # Читаем матрицу смежности
        adj_matrix = np.loadtxt(os.path.join(input_dir, filename))
        num_nodes = len(adj_matrix)
        
        # Создаем граф
        G = nx.Graph()
        G.add_nodes_from(range(num_nodes))
        
        # Добавляем ребра
        for i in range(num_nodes):
            for j in range(i+1, num_nodes):
                if adj_matrix[i][j] > 0:
                    G.add_edge(i, j, weight=adj_matrix[i][j])
        
        # Читаем эйлеров путь
        eulerian_path = []
        output_path = os.path.join(output_dir, filename)
        if os.path.exists(output_path):
            with open(output_path, 'r') as f:
                eulerian_path = list(map(int, f.read().split()))
        
        # Располагаем узлы на плоскости
        pos = nx.spring_layout(G, seed=42)  # Фиксированное расположение
        
        # Рисуем граф
        plt.figure(figsize=(10, 8))
        
        # Рисуем все узлы и ребра
        nx.draw_networkx_nodes(G, pos, node_size=300, node_color='lightblue')
        nx.draw_networkx_edges(G, pos, width=1, edge_color='gray')
        nx.draw_networkx_labels(G, pos)
        
        # Выделяем эйлеров путь
        if len(eulerian_path) > 1:
            path_edges = list(zip(eulerian_path[:-1], eulerian_path[1:]))
            nx.draw_networkx_edges(G, pos, edgelist=path_edges, 
                                  width=2, edge_color='red')
            
            # Подсвечиваем узлы в порядке пути
            for i, node in enumerate(eulerian_path):
                nx.draw_networkx_nodes(G, pos, nodelist=[node], 
                                      node_size=400, node_color='red', alpha=0.5)
                plt.text(pos[node][0], pos[node][1], str(i+1), 
                         color='white', ha='center', va='center')
        
        plt.title(f'Graph: {filename}\nEulerian Path: {"->".join(map(str, eulerian_path))}')
        plt.axis('off')
        
        # Сохраняем изображение
        output_image = os.path.join('visualizations', f'{filename[:-4]}.png')
        plt.savefig(output_image, bbox_inches='tight')
        plt.close()
        
        print(f'Saved visualization for {filename}')

# Обрабатываем все пары input/output
for i in range(1, 4):
    input_dir = f'input{i}'
    output_dir = f'output{i}'
    
    if os.path.exists(input_dir) and os.path.exists(output_dir):
        print(f'Processing {input_dir} and {output_dir}')
        visualize_graph_with_eulerian_path(input_dir, output_dir)
    else:
        print(f'Skipping {input_dir} or {output_dir} - not found')
