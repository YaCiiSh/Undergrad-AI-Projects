#include<iostream>
#include<limits.h>
#include<map>
#include<tuple>
#include<string>
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

queue <matrix> q_root, q_goal;
bool flag = false;
matrix rootMat, goalMat, sameMat, currentNodeRoot, currentNodeGoal;
int distanceFromRoot, cnt = 0;
map <string , tuple<string , int , string> > rootStore; //key : node & value : is a tuple of "parent of the node", "distance from root" and "the direction" 
map <string , tuple<string , int , string> > goalStore;
vector <string > pathVect_fromSametoGoal, pathVect_fromSametoRoot;

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

void path(){
	pathVect_fromSametoGoal.clear();
	pathVect_fromSametoRoot.clear();
	//cerr << "first part : " << endl;
	map <string , tuple<string , int , string> > :: iterator it;
	it = goalStore.find(convertMatrixtoString(sameMat));
	pathVect_fromSametoGoal.push_back(convertMatrixtoString(sameMat));
	while(get<0>(it -> second) != "111111111"){
		pathVect_fromSametoGoal.push_back(get<0>(it -> second));
		//cerr << "here: " << get<0>(it -> second) << endl;
		it = goalStore.find(get<0>(it -> second));
	}
	
	/*for(int i = 0; i < pathVect_fromSametoGoal.size(); i++){
		cout << pathVect_fromSametoGoal[i] << " ";
	}
	cout << endl;*/
	
	//cerr << "second part : " << endl;
	it = rootStore.find(convertMatrixtoString(sameMat));
	pathVect_fromSametoRoot.push_back(convertMatrixtoString(sameMat));
	while(get<0>(it -> second) != "000000000"){
		pathVect_fromSametoRoot.push_back(get<0>(it -> second));
		//cerr << "hereeeee: " << get<0>(it -> second) << endl;
		it = rootStore.find(get<0>(it -> second));
	}
	/*for(int i = 0; i < pathVect_fromSametoRoot.size(); i++){
		cout << pathVect_fromSametoRoot[i] << " ";
	}
	cout << endl;*/
	cout << endl << "Path is: " << endl;
	cout << "same node is: " << convertMatrixtoString(sameMat) << endl;
	cout << "Starting from sameNode to goalNode: " << endl;
	for(int i = 0; i < pathVect_fromSametoGoal.size() ; i++){
		cnt++;
		cout << pathVect_fromSametoGoal[i] << " "; 
	}
	cout << endl << endl;
	cout << "Starting from sameNode to rootNode: " << endl;
	for(int i = 0; i < pathVect_fromSametoRoot.size() ; i++){
		cnt++;
		cout << pathVect_fromSametoRoot[i] << " "; 
	}
	cout << endl;
	cout << "distance = " << cnt << endl;
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

string lookUp_rootStore(matrix mat){
	//cerr << "inside lookUp_rootStore." << endl;
	map< string , tuple<string , int , string> > :: iterator it;
	it = rootStore.find(convertMatrixtoString(mat));
	if(it == rootStore.end()){
		return "notFound";
	}
	else{
		//cout << "key: " << it -> first << " , value : " << get<o>(it -> second) << " , " << get<1>(it -> second) << endl;
		return "isFound";
	}
}

string lookUp_goalStore(matrix mat){
	//cerr << "inside lookUp_goalStore." << endl;
	map< string , tuple<string , int , string> > :: iterator it;
	it = goalStore.find(convertMatrixtoString(mat));
	if(it == goalStore.end()){
		return "notFound";
	}
	else{
		//cout << "key: " << it -> first << " , value : " << get<o>(it -> second) << " , " << get<1>(it -> second) << endl;
		return "isFound";
	}
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

void implementChildrenFromRoot(matrix node){
	//cerr << "inside implementChildrenFromRoot" << endl;
	pair<int , int> where_zero_is = findZero(node);
	//cerr << "where_zero_is.first: " << where_zero_is.first << " , where_zero_is.second: " << where_zero_is.second << endl;
	map <string , tuple<string , int , string> > :: iterator it;
	it = rootStore.find(convertMatrixtoString(node));
	distanceFromRoot = get<1>(it -> second);
	//cerr << "distanceFromRoot of node: " << distanceFromRoot << endl;
	if(0 <= (where_zero_is.first) && (where_zero_is.first) <= 2 && 0 <= (where_zero_is.second) - 1 && (where_zero_is.second) - 1 <= 2){
		matrix chL = node;
		swap(chL.a[where_zero_is.first][where_zero_is.second] , chL.a[where_zero_is.first][(where_zero_is.second) - 1]);
		//cerr << "left child: " << endl;
		//chL.display();
		if(lookUp_rootStore(chL) == "notFound"){
			//cerr << "chL is not found in the rootStore." << endl;
			rootStore.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chL) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "left")));
			q_root.push(chL);
			if(lookUp_goalStore(chL) == "isFound"){
				//cerr << "chL is found in the goal Store." << endl;
				sameMat = chL;
				flag = true;
				return;
			}  
		}
		else{
			//cerr << "chL was inserted in the rootStore before." << endl;
		}
	}
	if(0 <= (where_zero_is.first) - 1 && (where_zero_is.first) - 1 <= 2 && 0 <= (where_zero_is.second) && (where_zero_is.second) <= 2){
		matrix chU = node;
		swap(chU.a[where_zero_is.first][where_zero_is.second] , chU.a[(where_zero_is.first) - 1][(where_zero_is.second)]);
		//cerr << "up child : " << endl;
		//chU.display();
		if(lookUp_rootStore(chU) == "notFound"){
			//cerr << "chU is not found in the rootStore." << endl;
			rootStore.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chU) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "up")));
			q_root.push(chU);
			if(lookUp_goalStore(chU) == "isFound"){
				//cerr << "chU is found in the goal store." << endl;
				sameMat = chU;
				flag = true;
				return;
			}
		}
		else{
			//cerr << "chU was inserted in the rootStore before." << endl; 
		}
	}
	if(0 <= (where_zero_is.first) && (where_zero_is.first) <= 2 && 0 <= (where_zero_is.second) + 1 && (where_zero_is.second) + 1 <= 2){
		matrix chR = node;
		swap(chR.a[where_zero_is.first][where_zero_is.second] , chR.a[where_zero_is.first][(where_zero_is.second) + 1]);
		//cerr << "right child : " << endl;
		//chR.display();
		if(lookUp_rootStore(chR) == "notFound"){
			//cerr << "chR is not found in the rootStore." << endl;
			rootStore.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chR) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "right")));
			q_root.push(chR);
			if(lookUp_goalStore(chR) == "isFound"){
				//cerr << "chR in found in the goalStore." << endl;
				sameMat = chR;
				flag = true;
				return;
			}
			else{
				//cerr << "chR is not found in the goalStore.  " << endl;
			}
		}
		else{
			//cerr << "chR was inserted in the rootStore before." << endl;
		}
	}
	if(0 <= (where_zero_is.first) + 1 && (where_zero_is.first) + 1 <= 2 && 0 <= (where_zero_is.second) && (where_zero_is.second) <= 2){
		matrix chD = node;
		swap(chD.a[(where_zero_is.first)][where_zero_is.second] , chD.a[(where_zero_is.first) + 1][(where_zero_is.second)]);
		//cerr << "down child : " << endl;
		//chD.display();
		if(lookUp_rootStore(chD) == "notFound"){
			//cerr << "chD is not found in the rootStore." << endl;
			rootStore.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chD) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "down")));
			q_root.push(chD);
			if(lookUp_goalStore(chD) == "isFound"){
				//cerr << " chD is found in the goalStore." << endl;
				sameMat = chD;
				flag = true;
				return;
			}
		}
		else{
			//cerr << "chD was inserted in the rootStore before." << endl;
		}
	}
	return;
}

void implementChildrenFromGoal(matrix node){
	//cerr << "inside implementChildrenFromGoal" << endl;
	pair<int , int> where_zero_is = findZero(node);
	//cerr << "where_zero_is.first: " << where_zero_is.first << " , where_zero_is.second: " << where_zero_is.second << endl;
	map <string , tuple<string , int , string> > :: iterator it;
	it = goalStore.find(convertMatrixtoString(node));
	distanceFromRoot = get<1>(it -> second);
	if(0 <= (where_zero_is.first) && (where_zero_is.first) <= 2 && 0 <= (where_zero_is.second) - 1 && (where_zero_is.second) - 1 <= 2){
		matrix chL = node;
		swap(chL.a[where_zero_is.first][where_zero_is.second] , chL.a[where_zero_is.first][(where_zero_is.second) - 1]);
		//cerr << "left child: " << endl;
		//chL.display();
		if(lookUp_goalStore(chL) == "notFound"){
			//cerr << "chL is not found in the goalStore." << endl;
			goalStore.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chL) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "left")));
			q_goal.push(chL);
			if(lookUp_rootStore(chL) == "isFound"){
				//cerr << "chL is found in the rootStore." << endl;
				sameMat = chL;
				flag = true;
				return;
			}  
		}
		else{
			//cerr << "chL was inserted in the goalStore before." << endl;
		}
	}
	if(0 <= (where_zero_is.first) - 1 && (where_zero_is.first) - 1 <= 2 && 0 <= (where_zero_is.second) && (where_zero_is.second) <= 2){
		matrix chU = node;
		swap(chU.a[where_zero_is.first][where_zero_is.second] , chU.a[(where_zero_is.first) - 1][(where_zero_is.second)]);
		//cerr << "up child : " << endl;
		//chU.display();
		if(lookUp_goalStore(chU) == "notFound"){
			//cerr << "chU is not found in the goalStore." << endl;
			goalStore.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chU) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "up")));
			q_goal.push(chU);
			if(lookUp_rootStore(chU) == "isFound"){
				//cerr << "chU is found in the rootStore." << endl;
				sameMat = chU;
				flag = true;
				return;
			}
		}
		else{
			//cerr << "chU was inserted in the goalStore before." << endl;
		}
	}
	if(0 <= (where_zero_is.first) && (where_zero_is.first) <= 2 && 0 <= (where_zero_is.second) + 1 && (where_zero_is.second) + 1 <= 2){
		matrix chR = node;
		swap(chR.a[where_zero_is.first][where_zero_is.second] , chR.a[where_zero_is.first][(where_zero_is.second) + 1]);
		//cerr << "right child : " << endl;
		//chR.display();
		if(lookUp_goalStore(chR) == "notFound"){
			//cerr << "chR is not found in the goalStore." << endl;
			goalStore.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chR) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "right")));
			q_goal.push(chR);
			if(lookUp_rootStore(chR) == "isFound"){
				//cerr << "chR is found in the rootStore." << endl;
				sameMat = chR;
				flag = true;
				return;
			}
		}
		else{
			//cerr << "chR was inserted in the goalStore before." << endl;
		}
	}
	if(0 <= (where_zero_is.first) + 1 && (where_zero_is.first) + 1 <= 2 && 0 <= (where_zero_is.second) && (where_zero_is.second) <= 2){
		matrix chD = node;
		swap(chD.a[(where_zero_is.first)][where_zero_is.second] , chD.a[(where_zero_is.first) + 1][(where_zero_is.second)]);
		//cerr << "down child : " << endl;
		//chD.display();
		if(lookUp_goalStore(chD) == "notFound"){
			//cerr << "chD is not found in the goalStore." << endl;
			goalStore.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(chD) , make_tuple(convertMatrixtoString(node) ,(distanceFromRoot + 1) , "down")));
			q_goal.push(chD);
			if(lookUp_rootStore(chD) == "isFound"){
				//cerr << "chD is found in the rootStore." << endl;
				sameMat = chD;
				flag = true;
				return;
			}
		}
		else{
			//cerr << "chD was inserted in the goalStore before." << endl;
		}
	}
	return;

}


void bfsAlgorithm(){
	int counterOfBFS = 0;
	//cerr << "Inside bfs." << endl;
	q_root.push(rootMat);
	q_goal.push(goalMat);
	while(flag == false){
		cout << "loading #" << counterOfBFS << endl;
		currentNodeRoot = q_root.front();
		//cerr << "q_root front: " << endl;
		//currentNodeRoot.display();
		implementChildrenFromRoot(currentNodeRoot);
		currentNodeGoal = q_goal.front();
		//cerr << "q_goal front: " << endl;
		//currentNodeGoal.display();
		implementChildrenFromGoal(currentNodeGoal);
		q_root.pop();
		q_goal.pop();
		counterOfBFS++;
	}
	if(flag == true){
		return;
	}
	return;
}

int main(){
	rootStore.clear();
	goalStore.clear();
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
		int g[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
		goalMat.set(g);
		rootMat.set(entryArray);
		if(convertMatrixtoString(rootMat) == "123456780"){
			cout << "path is: \n123456780" << endl;
			return 0;
		}
		rootStore.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(rootMat) , make_tuple("000000000" , 0 , "null")));
		goalStore.insert(pair<string , tuple<string , int , string> > (convertMatrixtoString(goalMat) , make_tuple("111111111" , 0 , "null")));
		bfsAlgorithm();
		path();
	}
	return 0;
}
