/*input
(-3)^3+7*(-4)+2/5
*/
#include<bits/stdc++.h>
using namespace std;
///testai
///1+15*10-4/2
///149
///veikia

/// (10^2-3)*2
///194
///veikia

///(-3)^3+7*(-4)
///-55
struct veiksmai
{
	string eilute;
	vector<double> skaiciai;
	vector<pair<int, int> > skaiciuvieta;
	vector<char> operacijos;
	vector<int> tvarka;
	vector<int> gylis;
	veiksmai(string eil)
	{
		eilute = eil;
		Skaiciai();
		RaskVeiksmus();
		//SpausdintiViska();
		Skaiciuoti();
		SpausdintiViska();
	}
	veiksmai() { }
	void Skaiciai()
	{
		//cout << "nu ok";
		for(int i=0; i<eilute.size(); i++)
		{
			if(('0'<=eilute[i]) && (eilute[i]<='9'))
			{
				double naujas = 0;
				int kitas;
				for(kitas = i+1; i<eilute.size(); kitas++)
				{
					if((eilute[kitas]<'0') || ('9'<eilute[kitas]))
						break;
				}
				//cout << i << " " << kitas << endl;
				for(int j=i; j<kitas; j++)
				{
					naujas *= 10;
					naujas += eilute[j]-'0';
				}
				if(eilute[kitas]=='.')
				{
					double daug = 1;
					for(int j=kitas+1; j<eilute.size(); j++)
					{
						daug /= 10;
						if(('0'<=eilute[i]) && (eilute[i]<='9'))
							naujas += daug * (eilute[i]-'0');
						else
							break;
					}
				}
				skaiciai.push_back(naujas);
				skaiciuvieta.push_back(make_pair(i, kitas-1));
				i = kitas -1;
			}
		}
		neigiami();
	}
	void neigiami()
	{
		for(int i=0; i<skaiciai.size(); i++)
		{
			if((skaiciuvieta[i].first>=2) && (skaiciuvieta[i].second!=eilute.size()-1))
			{
				if((eilute[skaiciuvieta[i].first-1]=='-') && (eilute[skaiciuvieta[i].first-2]=='(') && (eilute[skaiciuvieta[i].second +1]==')'))
				{
					skaiciai[i] = - skaiciai[i];
					eilute[skaiciuvieta[i].first-1] = '_';			

				}
			}
		}
	}
	void SpausdintiViska()
	{
		for(int i=0; i<skaiciai.size(); i++)
			cout << skaiciai[i] << " ";
		cout << endl;
		for(int i=0; i<operacijos.size(); i++)
			cout << operacijos[i] << " ";
		cout << endl;

	}
	void RaskVeiksmus()
	{
		int skl = 0;
		for(int i=0; i<eilute.size(); i++)
		{
			if(eilute[i]=='(')
				skl++;
			else if (eilute[i]==')')
				skl--;
			else if((eilute[i]<'0') || ('9'<eilute[i]))
			{
				if(eilute[i]!='_')
				{
					operacijos.push_back(eilute[i]);
					if(eilute[i]=='^')
						tvarka.push_back(2);
					else if ((eilute[i]=='*') || (eilute[i]=='/'))
						tvarka.push_back(1);
					else
						tvarka.push_back(0);
					gylis.push_back(skl);					
				}

			}
		}
		tvarkon();
	}

	void tvarkon()
	{
		int max_gylis = 0;
		for(int i=0; i<gylis.size(); i++)
			max_gylis = max(max_gylis, gylis[i]);
		int veiksmu_skaicius = operacijos.size() * 4;
		for(int i=0; i<operacijos.size(); i++)
			tvarka[i] = veiksmu_skaicius * gylis[i] + tvarka[i];
	}

	void Skaiciuoti()
	{
		while(skaiciai.size()!=1)
		{
			SpausdintiViska();
			int maxi = -1;
			int numeris = 0;
			for(int i=0; i<tvarka.size(); i++)
			{
				if(tvarka[i]>maxi)
				{
					maxi = tvarka[i];
					numeris = i;
				}
			}
			if(operacijos[numeris]=='^')
				skaiciai[numeris] = pow(skaiciai[numeris], skaiciai[numeris+1]);
			else if (operacijos[numeris]=='*')
				skaiciai[numeris] = skaiciai[numeris] * skaiciai[numeris+1];
			else if(operacijos[numeris]=='/')
				skaiciai[numeris] = skaiciai[numeris] / skaiciai[numeris+1];
			else if (operacijos[numeris]=='+')
				skaiciai[numeris] = skaiciai[numeris] + skaiciai[numeris+1];
			else if(operacijos[numeris]=='-')
				skaiciai[numeris] = skaiciai[numeris] - skaiciai[numeris+1];
			for(int j = numeris+1; j<skaiciai.size()-1; j++)
				skaiciai[j] = skaiciai[j+1];
			skaiciai.pop_back();
			for(int j=numeris; j<operacijos.size()-1; j++)
			{
				tvarka[j] = tvarka[j+1];
				operacijos[j] = operacijos[j+1];
				gylis[j] = gylis[j+1];
			}
			tvarka.pop_back();
			operacijos.pop_back();
			gylis.pop_back();
		}

	}


};

int main()
{
	string eilute;
	cin >> eilute;
	cout << eilute << endl;
	veiksmai uzduotis(eilute);
	return 0;
}