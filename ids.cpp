#include<iostream>
#include<limits.h>
#include<map>
#include<tuple>
#include<string>
using namespace std;
class matrix{	
	public:	 
		int a[3][3];
		
		void set(int b[3][3] ){
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					a[i][j] = b[i][j];
				}
			}
		}
		
		void display(){
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					cout << a[i][j] << " ";
				}
				cout << endl;
			}
		} 
			
};

bool flag;
matrix entryMat;
int distanceFromRoot;
map <string , tuple<string , int , string> > store; //key : node & value is a tuple of "parent of the node", "distance from root" and "the direction" 

matrix convertStringtoMatrix(string str){
	int cnt = 0;
	int arr[3][3];
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			arr[i][j] = str[cnt] - 48;
			cnt++;
		}
	}
	matrix mat;
	mat.set(arr);
	return mat;
}

void path(){
	cout << "the reverse path is: " << endl;
	map <string , tuple<string , int , string> > :: iterator it;
	it = store.find("123456780");
	cout << "Distance of the goal node from root is: " << get<1>(it -> second) << endl;
	convertStringtoMatrix("123456780").display();
	cout << "********************************" << endl;
	cout << "go through this direction: " << get<2>(it -> second) << endl;
	convertStringtoMatrix(get<0>(it -> second)).display();
	cout << "********************************" << endl;
	while(get<0>(it -> second) != "000000000" && it != store.end()){
		it = store.find(get<0>(it -> second));
		cout << "go through this direction: " << get<2>(it -> second) << endl;
		convertStringtoMatrix(get<0>(it -> second)).display();
		cout << "********************************" << endl;
	}
	return;
	
}

string solvabilityOfPuzzle(int arr[3][3]){
	//cerr << "here";
	int oneDarray[9];
	int c = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			oneDarray[c] = arr[i][j];
			c++;
		}
	}
	/*cout << "print oneDarray:" << endl;
	for(int i = 0; i < 9; i++){
		cout << oneDarray[i] << " ";
	}
	cout << endl;*/
	int count = 0;
	for(int i = 0; i < 8; i++){
		for(int j = i + 1; j < 9; j++){
			if(oneDarray[i] != 0 && oneDarray[j] != 0 && oneDarray[i] > oneDarray[j]){
				count++;
			}
		}
	}
	//cout << "count = " << count;
	if(count % 2 == 0){
		return "solvable";
	}
	else 
		return "unsolvable";
	
}

bool compare(matrix m1 , matrix m2){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(m1.a[i][j] != m2.a[i][j]){
				return false;//false means that they are not the same.
			}
		}
	}
	return true;//true means that they are the same.
}

string convertMatrixtoString(matrix mat){
	string answer;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			answer += to_string(mat.a[i][j]);
		}
	}
	return answer;
}

string lookUp_store(matrix mat){
	map< string , tuple<string , int , string> > :: iterator it;
	it = store.find(convertMatrixtoString(mat));
	if(it == store.end()){
		return "notFound";
	}
	else{
		//cout << "key: " << it -> first << " , value : " << get<o>(it -> second) << " , " << get<1>(it -> second) << endl;
		return "isFound";
	}
}
		
bool goalTest(matrix mat){
	if(mat.a[0][0] == 1 && mat.a[0][1] == 2 && mat.a[0][2] == 3 && mat.a[1][0] == 4 && mat.a[1][1] == 5 && mat.a[1][2] == 6 && mat.a[2][0] == 7 && mat.a[2][1] == 8 && mat.a[2][2] == 0)
		return true;
	return false;	
}
	
pair<int , int> findZero (matrix m){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(m.a[i][j] == 0){
				//cerr << "zero is here: row is : " << i << " and, colomn is: " << j << endl; 
				return make_pair(i , j);
			}
		}
	}
}

bool dls_algorithm(matrix node , int length , int distanceFromRoot){
	if(goalTest(node) == true){
		flag = true;
		return true;
	} 
	else{
		if(0 <= distanceFromRoot && distanceFromRoot <= length){
			pair<int , int> where_zero_is = findZero(node);
			//cerr << "length = " << length << endl;
			//cerr << endl << "parent:" << endl;
			//node.display();
			if(0 <= (where_zero_is.first) && (where_zero_is.first) <= 2 && 0 <= (where_zero_is.second) - 1 && (where_zero_is.second) - 1 <= 2){
				matrix chL = node;
				swap(chL.a[where_zero_is.first][where_zero_is.second] , chL.a[where_zero_is.first][(where_zero_is.second) - 1]);
				//cerr << "left child: " << endl;
				//chL.display();
				if(goalTest(chL) == true){
					store.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chL) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "left")));
					flag = true;
					return true;
				}
				if(lookUp_store(chL) == "notFound"){
					store.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chL) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "left")));
					dls_algorithm(chL , length, distanceFromRoot + 1);
				}
				else {
					//cout << "chL had been visited before." << endl;
				}
			}
		
			if(0 <= (where_zero_is.first) - 1 && (where_zero_is.first) - 1 <= 2 && 0 <= (where_zero_is.second) && (where_zero_is.second) <= 2){
				matrix chU = node;
				swap(chU.a[where_zero_is.first][where_zero_is.second] , chU.a[(where_zero_is.first) - 1][(where_zero_is.second)]);
				//cerr << "up child : " << endl;
				//chU.display();
				if(goalTest(chU) == true){
					store.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chU) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "up")));
					flag = true;
					return true;
				}
				if(lookUp_store(chU) == "notFound"){
					store.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chU) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "up")));
					dls_algorithm(chU , length, distanceFromRoot + 1);
				}
				else{
					//cout << "chU had been visited before." << endl;
				}
			}
		
			if(0 <= (where_zero_is.first) && (where_zero_is.first) <= 2 && 0 <= (where_zero_is.second) + 1 && (where_zero_is.second) + 1 <= 2){
				matrix chR = node;
				swap(chR.a[where_zero_is.first][where_zero_is.second] , chR.a[where_zero_is.first][(where_zero_is.second) + 1]);
				//cerr << "right child : " << endl;
				//chR.display();
				if(goalTest(chR) == true){
					store.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chR) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "right")));
					flag = true;
					return true;
				}
				if(lookUp_store(chR) == "notFound"){
					store.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chR) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "right")));
					dls_algorithm(chR , length, distanceFromRoot + 1);
				}
				else {
					//cout << "chR had been visited before." << endl;
				}
			}
		
			if(0 <= (where_zero_is.first) + 1 && (where_zero_is.first) + 1 <= 2 && 0 <= (where_zero_is.second) && (where_zero_is.second) <= 2){
				matrix chD = node;
				swap(chD.a[(where_zero_is.first)][where_zero_is.second] , chD.a[(where_zero_is.first) + 1][(where_zero_is.second)]);
				//cerr << "down child : " << endl;
				//chD.display();
				if(goalTest(chD) == true){
					store.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chD) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "down")));
					flag = true;
					return true;
				}
				if(lookUp_store(chD) == "notFound"){
					store.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chD) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "down")));
					dls_algorithm(chD , length, distanceFromRoot + 1);
				}
				else{
					//cout << "chD had been visited before." << endl;
				}
			}
			
		}
		return false;
	}
}

string ids_algorithm(){
	for(int len = 0; len < INT_MAX; len++){
		cerr << "loading #" << len << endl;
		store.clear();
		flag = false;
		store.insert(pair< string , tuple<string , int , string> >(convertMatrixtoString(entryMat) , make_tuple ("000000000" , 0 , "null")));
		dls_algorithm(entryMat , len , 0);
		if(flag == true){
			cout << "len: " << len << endl;
			return "isFound";
			
		}
	}
	return "notFound";
}

int main(){
	store.clear();
	cout << "Enter your puzzle: " << endl; //enter a shuffled representation of numbers between 0 and 8. e.g. 6 8 4 5 7 1 0 2 3
	int entryArray[3][3];
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			cin >> entryArray[i][j];
		}
	}
	
	if(solvabilityOfPuzzle(entryArray) == "unsolvable"){
		cout << "This puzzle is not solvable :)))";
		return 0;	
	}
	else{
		cout << "This puzzle is solvable." << endl;
		entryMat.set(entryArray);
		store.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(entryMat) , make_tuple("000000000" , 0 , "null")));
		if(ids_algorithm() == "isFound"){
			cout << "We have reached the Goal node!!" << endl;
			path();
			return 0;
		}
	}
}
