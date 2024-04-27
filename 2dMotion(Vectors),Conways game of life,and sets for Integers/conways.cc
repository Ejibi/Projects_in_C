#include <iostream>
#include <string>

using namespace std;

struct Matrix {
    char **matrix;
    int init_rows = 0;
    int num_columns;
    int true_rows=0;
};

void start(struct Matrix *row, const int num_columns) {
    (*row).num_columns = num_columns;
    (*row).matrix = new char*[1];
    for (int i = 0; i < 1; ++i) {
        (*row).matrix[i] = new char[num_columns];
    }
    (*row).init_rows++;
}

void GO(struct Matrix *row, const char *new_row, int num_row) {
    if ((*row).true_rows == (*row).init_rows &&  num_row != 1) {
        char **new_matrix = new char*[(*row).init_rows * 2];
        for (int i = 0; i < (*row).init_rows * 2; ++i) {
            new_matrix[i] = new char[(*row).num_columns];
        }
        for (int j = 0; j < (*row).true_rows; ++j) {
            for (int k = 0; k < (*row).num_columns; ++k) {
                new_matrix[j][k] = (*row).matrix[j][k];
            };
        }
        for (int k = 0; k < (*row).num_columns; ++k) {
            new_matrix[(*row).true_rows][k] = new_row[k];
        }
        (*row).true_rows++;
        for (int i = 0; i < (*row).init_rows; ++i) {
            delete[] (*row).matrix[i];
        }
        delete[] (*row).matrix;
        (*row).matrix = new_matrix;
        (*row).init_rows = (*row).init_rows * 2;
    } 
    else{
        for (int k = 0; k < (*row).num_columns; ++k) {
            (*row).matrix[(*row).true_rows][k] = new_row[k];
        }
        (*row).true_rows++;
    }
}

void printMatrix(const Matrix &row) {
    
    for (int j = 0; j < row.num_columns; ++j){
        cout<<'|';
        }
    cout << endl;
    for (int i = 0; i < row.true_rows; ++i) {
        for (int j = 0; j < row.num_columns; ++j) {
            cout << row.matrix[i][j];
        }
        cout << endl;
    }
    for (int j = 0; j < row.num_columns; ++j){
        cout<<'|';
        }
    cout << endl;
}

int living(const struct Matrix *matrow,int row,int column){
    int lives =0;
    int full[]={-1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1};
    for(int i =0;i<16;i+=2){
        int check_row= row + full[i]; 
        int check_column= column + full[i+1];
        if (check_row>=0 && check_column >=0 && check_row < (*matrow).true_rows && check_column < (*matrow).num_columns && (*matrow).matrix[check_row][check_column] == 'O'){
            lives++;
        }
    }
    return lives;
}

void progress(struct Matrix *row){
    char **new_matrix = new char*[(*row).init_rows];
    for (int i = 0; i < (*row).init_rows; ++i) {
        new_matrix[i] = new char[(*row).num_columns];
    }
    for (int j = 0; j < (*row).true_rows; ++j) {
        for (int k = 0; k < (*row).num_columns; ++k) {
            new_matrix[j][k] = (*row).matrix[j][k];
        };
    }
    for (int i = 0; i < (*row).true_rows; ++i) {
        for (int j = 0; j < (*row).num_columns; ++j) {
            int around = living(row,i,j);
            if((*row).matrix[i][j] == 'O'){
                if (around < 2 || around > 3){
                    new_matrix[i][j] = '.';
                }
            }
            else{
                if (around == 3){
                    new_matrix[i][j] = 'O';
                }
            }
        }
    }
    for (int i = 0; i < (*row).init_rows; ++i) {
        delete[] (*row).matrix[i];
    }
    delete[] (*row).matrix;
    (*row).matrix = new_matrix;
}
int main() {
    Matrix mat;
    string line;
    getline(cin, line);
    int columns=line.length();
    start(&mat, columns);
    int i=1;
    GO(&mat, line.c_str(), i);
    while (true) {
        string line;
        getline(cin, line);
        if (line[0]=='x') {
            break; 
        }
        if (mat.init_rows == 0) {
            start(&mat, line.length());
        } else {
            i++;
            GO(&mat, line.c_str(), i);
        }
    }
    char command;
    while (cin >> command) {
        if (command == 'p') {
            printMatrix(mat);
        } else if (command == 's') {
            progress(&mat);
        }
    }
    for (int i = 0; i < mat.init_rows; ++i) {
        delete[] mat.matrix[i];
    }
    delete[] mat.matrix;
    return 0;
}