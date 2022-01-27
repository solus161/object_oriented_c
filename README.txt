gcc -shared -fPIC -o liblistint.so listint.c
gcc test_listint.c -L /home/quangnguyen/projects/ooc/python_data_structure -llistint -o test_listint

gcc -shared -fPIC -o libnew.so new.c
gcc -shared -fPIC -o libpystruct.so pystruct.c
gcc test_pystruct.c -L /home/quangnguyen/projects/ooc/python_data_structure -lnew -lpystruct -o test_pystruct