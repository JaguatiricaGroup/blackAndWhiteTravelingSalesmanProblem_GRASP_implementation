vector<int>* leArquivo(char* arquivo){
	ifstream k(arquivo);
	vector<int>* saida=new vector<int>();
	if(k.is_good()){
		while(!k.eof()){
			string aux;
			getline(k,aux);
			saida->push_back(stoi(aux));
		}
	}else{
		cout << "arquivo nao existe" << endl;
	}
}

double media(vector<int>* numeros){
	int soma=0;
	for(int &i:*numeros){
		soma+=i;
	}
	return (double)soma/numeros.size();
}

double desvioPadrao(vector<int>* numeros,double media){
	double desvio=0;
	for(int &k:*numeros){
		desvio+=pow((k-media),2)
	}
	return desvio/numeros->size();
}

main(int argc,char **arvg){
	le
}
