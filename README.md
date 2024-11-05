# AVLTree

## Описание 
Здесь реализовано AVL дерево и сравнение скорости его работы с std::set

## Сборка и запуск
Для сборки программы реализующей необходимо:
> cmake -DCMAKE_BUILD_TYPE=Release -S . -B build\
> cd build\
> make

__Cтандартный режим__
> ./avltree.x

__Прохождение встроенных p2p тестов__
> ./avltree.test

__Прохождение встроенных ubit тестов__
> ./avltree.unit

## Сравнение
> cd compare\
> python3 generate.py\
> python3 compare.py
