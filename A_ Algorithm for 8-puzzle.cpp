#include<iostream>
#include<map>
#include<tuple>
#include<vector>
#include<limits.h>
#include<algorithm>
#include<queue>
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

matrix entryMat, node, childMat, chL, chU, chR, chD;
int hL, hU, hR, hD, fL, fU, fR, fD, distanceFromRoot, counter;
pair<int , int> currentPlc, realPlc, where_zero_is, crtPlc, relPlc;
tuple <int , string , string , string> chosenChild;
map <string , tuple<string , int , string> > store; //key : node & value is a tuple of "parent of the node", "distance from root" and "the direction"
//vector < tuple <int , string , string , string> > nodes; // f , node , parent , direction
priority_queue <tuple <int , string , string , string> , vector<tuple <int , string , string , string> > , greater<tuple <int , string , string , string> > > nodes; // f , node , parent , direction

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

string convertMatrixtoString(matrix mat){
	string answer;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			answer += to_string(mat.a[i][j]);
		}
	}
	return answer;
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

//function for finding the current place:
pair<int , int> currentPlace(int numb , matrix mat){
	//cerr << "inside currentPlace: " << numb << endl;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(mat.a[i][j] == numb){
				//cerr << "currentPlace: row = " << i << " , column = " << j << endl;
        return make_pair(i , j);
      }
    }
  }
}

//function for finding the real place:
pair<int , int> realPlace(int numb){
	//cerr << "inside realPlace: " << numb << endl;
  if(numb == 1) return make_pair(0 , 0);
  if(numb == 2) return make_pair(0 , 1);
  if(numb == 3) return make_pair(0 , 2);
  if(numb == 4) return make_pair(1 , 0);
  if(numb == 5) return make_pair(1 , 1);
  if(numb == 6) return make_pair(1 , 2);
  if(numb == 7) return make_pair(2 , 0);
  if(numb == 8) return make_pair(2 , 1);
  if(numb == 0) return make_pair(2 , 2);
}

// This function gives us the "h":
int returnDistFromRoot (matrix mat){
  map< string , tuple<string , int , string> > :: iterator it;
  it = store.find(convertMatrixtoString(mat));
	//cerr << "distanceFromRoot = " << get<1>(it -> second) << endl;
  return get<1>(it -> second);
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

int manhattan_distance (matrix mat){
   int sum = 0;	
   for(int i = 0; i < 3; i++){
   	for(int j = 0; j < 3; j++){
   		crtPlc = currentPlace(mat.a[i][j] , mat);
   		relPlc = realPlace(mat.a[i][j]);
   		//cerr << crtPlc.first << " " << crtPlc.second << " " << relPlc.first << " " << relPlc.second << " ";
   		sum += (abs(crtPlc.first - relPlc.first) + abs(crtPlc.second - relPlc.second));
	   }
   }
   return sum; 
}

bool goalTest(matrix mat){
 if(mat.a[0][0] == 1 && mat.a[0][1] == 2 && mat.a[0][2] == 3 && mat.a[1][0] == 4 && mat.a[1][1] == 5 && mat.a[1][2] == 6 && mat.a[2][0] == 7 && mat.a[2][1] == 8 && mat.a[2][2] == 0)
  return true;
 return false;
}

void path(){
	cout << "The reverse path is: " << endl;
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

void makeChildren(matrix mat){
	//cerr << "inside makeChildren function" << endl;
	hL = 0, hU = 0, hR = 0, hD = 0, fL = 0, fU = 0, fR = 0, fD = 0;
	where_zero_is = findZero(mat);
  	distanceFromRoot = returnDistFromRoot(mat);
	if(0 <= (where_zero_is.first) && (where_zero_is.first) <= 2 && 0 <= (where_zero_is.second) - 1 && (where_zero_is.second) - 1 <= 2){
		chL = mat;
		swap(chL.a[where_zero_is.first][where_zero_is.second] , chL.a[where_zero_is.first][(where_zero_is.second) - 1]);
		hL = manhattan_distance(chL);
		fL = hL + distanceFromRoot;
		if(lookUp_store(chL) == "notFound"){
			nodes.push(make_tuple(fL , convertMatrixtoString(chL) , convertMatrixtoString(mat) , "L"));	
		}
		//cerr << "chL: " << fL << " " << convertMatrixtoString(chL) << " " << convertMatrixtoString(mat) << endl;
  	}

	if(0 <= (where_zero_is.first) - 1 && (where_zero_is.first) - 1 <= 2 && 0 <= (where_zero_is.second) && (where_zero_is.second) <= 2){
		chU = mat;
		swap(chU.a[where_zero_is.first][where_zero_is.second] , chU.a[(where_zero_is.first) - 1][(where_zero_is.second)]);
  		hU = manhattan_distance(chU);
    	fU = hU + distanceFromRoot;
    	if(lookUp_store(chU) == "notFound"){
			nodes.push(make_tuple(fU , convertMatrixtoString(chU) , convertMatrixtoString(mat) , "U"));	
		}
    	//cerr << "chU: " << fU << " " << convertMatrixtoString(chU) << " " << convertMatrixtoString(mat) << endl;
   	}

	if(0 <= (where_zero_is.first) && (where_zero_is.first) <= 2 && 0 <= (where_zero_is.second) + 1 && (where_zero_is.second) + 1 <= 2){
		chR = mat;
		swap(chR.a[where_zero_is.first][where_zero_is.second] , chR.a[where_zero_is.first][(where_zero_is.second) + 1]);
		hR = manhattan_distance(chR);
		fR = hR + distanceFromRoot;
		if(lookUp_store(chR) == "notFound"){
			nodes.push(make_tuple(fR , convertMatrixtoString(chR) , convertMatrixtoString(mat) , "R"));	
		}
		//cerr << "chR: " << fR << " " << convertMatrixtoString(chR) << " " << convertMatrixtoString(mat) << endl;
  	}

	if(0 <= (where_zero_is.first) + 1 && (where_zero_is.first) + 1 <= 2 && 0 <= (where_zero_is.second) && (where_zero_is.second) <= 2){
		chD = mat;
		swap(chD.a[(where_zero_is.first)][where_zero_is.second] , chD.a[(where_zero_is.first) + 1][(where_zero_is.second)]);
		hD = manhattan_distance(chD);
		fD = hD + distanceFromRoot;
		if(lookUp_store(chD) == "notFound"){
			nodes.push(make_tuple(fD , convertMatrixtoString(chD) , convertMatrixtoString(mat) , "D"));	
		}
		//cerr << "chD: " << fD << " " << convertMatrixtoString(chD) << " " << convertMatrixtoString(mat) << endl;
  	}
  	return;
}

string A_star_algorithm (){
	counter = 1;
	makeChildren(entryMat);
	chosenChild = nodes.top();
	//cerr << "chosenChild: " << " " << get<1>(chosenChild) << " " << get<2>(chosenChild) << " " << get<3>(chosenChild) << endl;
	nodes.pop();
	while(goalTest(convertStringtoMatrix(get<1>(chosenChild))) != true){
		//cerr << "begining of the while loop" << endl;
		if(lookUp_store(convertStringtoMatrix(get<1>(chosenChild))) == "notFound"){
			//cerr << " inja miyay???" << endl;
			store.insert(pair<string , tuple<string , int , string> > (get<1>(chosenChild) , make_tuple(get<2>(chosenChild) , returnDistFromRoot(convertStringtoMatrix(get<2>(chosenChild))) + 1 , get<3>(chosenChild))));
			makeChildren(convertStringtoMatrix(get<1>(chosenChild)));
			//cerr << "inside second if in a star algo: " <<  get<1>(chosenChild) << " " << get<2>(chosenChild) << " " << get<3>(chosenChild) << endl;
  		}
		chosenChild = nodes.top();
		//cerr << "chosenChild: " << " " << get<0>(chosenChild) << " " << get<1>(chosenChild) << " " << get<2>(chosenChild) << " " << get<3>(chosenChild) << endl;
		nodes.pop();
		counter++;	
		//cerr << "at the end of while loop" << endl;
	}
	if(goalTest(convertStringtoMatrix(get<1>(chosenChild))) == true){
		store.insert(pair<string , tuple<string , int , string> > (get<1>(chosenChild) , make_tuple(get<2>(chosenChild) , returnDistFromRoot(convertStringtoMatrix(get<2>(chosenChild))) + 1 , get<3>(chosenChild))));
		//cerr << "inja" << endl;
		return "finished";
	}
}

int main(){
  store.clear();
  cout << "Enter your puzzle:" << endl; //enter a shuffled representation of numbers between 0 and 8. e.g. 6 8 4 5 7 1 0 2 3
  int entryArray[3][3];
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			cin >> entryArray[i][j];
		}
	}
  entryMat.set(entryArray);
  
  if(solvabilityOfPuzzle(entryArray) == "unsolvable"){
		cout << "This puzzle is not solvable :)))";
		return 0;
	}
	else{
    	cout << "This puzzle is solvable." << endl;
    	//makeChildren(entryMat);
    	if(goalTest(entryMat) == true){
    		cout << "This puzzle was goal, initially." << endl;
    		return 0;
		}
    	store.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(entryMat) , make_tuple("000000000" , 0 , "null")));
		if(A_star_algorithm() == "finished"){
		cout << "the puzzle solved" << endl;
		path();
		}
		else{
			cout << "could not solved." << endl;
		}
  }
  return 0;
}
