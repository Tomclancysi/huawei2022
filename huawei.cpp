//#include<iostream>
//#include<algorithm>
//#include<vector>
//#include<string>
//#include<cstring>
//#include<fstream>
//#include<functional>
//#include<utility>
//#include<exception>
//#include<unordered_set>
//#include<unordered_map>
//#define TEST
//#define CHECKANS
//using namespace std;
//using ll = long long;
//
//ll sum_all[300];
//int rank[300];
//int distri[300][150]; // ÏÈ»úÆ÷ ºóÓÃ»§¶àÉÙ
//int site_load[300];
//int vis[300];
//int fa[300];
//int father(int x) {
//	return x == fa[x] ? x : fa[x] = father(fa[x]);
//}
//
//int main() {
//#ifdef TEST
//	string prefix = "C:\\Users\\LiNing\\Desktop\\ÏßÏÂµ÷ÊÔÊý¾Ý\\data\\";
//#else
//	string prefix = "/data/";
//#endif // TEST
//
//	cin.tie(0);
//	cout.tie(0);
//	for (int i = 0; i < 300; ++i)fa[i] = i;
//	ifstream fin(prefix + "demand.csv");
//	string line;
//	vector<string> clients;
//	vector<vector<int>> needs;
//	unordered_map<string, int> clientname2idx;
//	fin >> line;
//	for (int i = 0, j = 0; i < line.size();) {
//		while (j < line.size() && line[j] != ',')++j;
//		if (i != 0) {
//			clients.push_back(line.substr(i, j - i));
//			clientname2idx[clients.back()] = clients.size() - 1;
//		}
//		i = j + 1;
//		j = i;
//	}
//
//	while (fin >> line) {
//		vector<int> need;
//		for (int i = 0, j = 0; i < line.size();) {
//			while (j < line.size() && line[j] != ',')++j;
//			if (i != 0) {
//				need.push_back(stoi(line.substr(i, j - i)));
//			}
//			i = j + 1;
//			j = i;
//		}
//		needs.push_back(need);
//	}
//	cout << "demand readed\n";
//
//	vector<string> sites;
//	vector<int> sites_flow;
//	vector<pair<int, int>> du_of_site;
//	ifstream fin_siteinfo(prefix + "site_bandwidth.csv");
//	unordered_map<string, int> sitename2idx;
//	fin_siteinfo >> line;
//	while (fin_siteinfo >> line) {
//		int dot = line.find_first_of(',');
//		sites.push_back(line.substr(0, dot));
//		sitename2idx[sites.back()] = sites.size() - 1;
//		sites_flow.push_back(stoi(line.substr(dot + 1)));
//	}
//	for (int i = 0; i < sites.size(); ++i)du_of_site.push_back({0, i}); // {du, site}
//	cout << "site info readed\n";
//
//	ifstream fin_config(prefix + "config.ini");
//	fin_config >> line >> line;
//	int constraint = stoi(line.substr(line.find_first_of('=')+1));
//	cout << "constraint readed\n";
//
//	int client_num = clients.size(), site_num = sites.size();
//	int client_offset = 0, site_offset = client_num;
//	vector<vector<int>> valid(site_num, vector<int>(client_num));
//	vector<vector<int>> G(client_num + site_num);
//	
//	ifstream fin_qos(prefix + "qos.csv");
//	fin_qos >> line;
//	vector<int> cltid;
//	for (int i = 0, j = 0; i < line.size();) {
//		while (j < line.size() && line[j] != ',')++j;
//		if (i != 0) {
//			cltid.push_back(clientname2idx[line.substr(i, j - i)]);
//		}
//		i = j + 1;
//		j = i;
//	}
//	int row = 0;
//	while (fin_qos >> line) {
//		int cur_siteid = -1;
//		for (int i = 0, j = 0, col = 0; i < line.size();) {
//			while (j < line.size() && line[j] != ',')++j;
//			if (i != 0) {
//				int qos = stoi(line.substr(i, j - i));
//				int cur_cltid = cltid[col];
//				if (qos < constraint) {
//					du_of_site[cur_siteid].first += 1;
//					valid[cur_siteid][cur_cltid] = 1;
//					G[site_offset + cur_siteid].push_back(cur_cltid);
//					G[cur_cltid].push_back(site_offset + cur_siteid);
//				}
//				++col;
//			}
//			else {
//				cur_siteid = sitename2idx[line.substr(i, j - i)];
//			}
//			i = j + 1;
//			j = i;
//		}
//		++row;
//	}
//	cout << "qos readed\n";
//	sort(du_of_site.begin(), du_of_site.end());
//	reverse(du_of_site.begin(), du_of_site.end());
//	int topk = sites.size() / 5;
//	unordered_set<int> popular_site;
//	for (int i = 0; i < topk; ++i) popular_site.insert(du_of_site[i].second + site_offset);
//	
//	function<bool(int, vector<int>&, int, bool) > dfs = [&](int st, vector<int>& pth, int minval, bool urgent) {
//		if (vis[st])return false;
//		pth.push_back(st);
//		vis[st] = 1;
//		if (st >= site_offset && site_load[st] > 0 && (urgent || (!urgent && popular_site.count(st)))) {// ÕÒµ½¿ÉÒÔ×ªÒÆµÄÎ»ÖÃ
//			int load = min(minval, site_load[st]);// ×ªÒÆÁ¿
//			// ÐÞ¸ÄÕâÌõÂ·¾¶ÉÏµÄÖµ
//			site_load[pth[0]] += load;
//			
//			// ¶ÔÓÚÂ·¾¶ÖÐ¼äµÄ½Úµã£¬ËüµÄ¸ºÔØÓ¦¸Ã²»±ä£¬Ö»ÊÇÂ·¹ý¶øÒÑ
//			for (int i = 1, j = pth.size(); i < j; i += 2) {
//				distri[pth[i-1]][pth[i]] -= load;
//				distri[pth[i+1]][pth[i]] += load;
//			}
//
//			site_load[st] -= load;
//			return true;
//		}
//		else {// ¼ÌÐøËÑË÷ÄÜ¹»°²·ÅµÄµØ·½
//			for (auto next : G[st]) {
//				if (next >= site_offset) {// ´ÓÏÂµ½ÉÏ£¬ nextÎª·þÎñÆ÷,ÕâÀï¶Ô·ÖÅäÁ¿¾ÍÃ»ÓÐÒªÇó
//					if (!vis[next]) {
//						if (dfs(next, pth, minval, urgent))
//							return true;
//					}
//				}
//				else {// ´ÓÉÏµ½ÏÂ, stÎª·þÎñÆ÷£¬±íÊ¾ÕâÌõ·ÖÅä±ß½«Òª¼õÉÙ£¬´óÓÚ0
//					if (distri[st][next] > 0) {
//						if (dfs(next, pth, min(distri[st][next], minval), urgent))
//							return true;
//					}
//				}
//			}
//		}
//		vis[st] = 0;
//		pth.pop_back();
//		return false;
//	};
//#ifdef TEST
//	ofstream out("./temp.txt"); // TODO change  /output/solution.txt
//#else
//	ofstream out("/output/solution.txt"); // TODO change  
//#endif // TEST
//	for (auto need : needs) {
//		for (int i = 0; i < site_num; ++i)site_load[i + site_offset] = sites_flow[i];
//		memset(distri, 0, sizeof distri);
//		// Ã¿¸öÓÃ»§µÄÐèÇó´óÐ¡£¬ÏÈÆ½¾ùµÄ·ÖÅä¸øËüÄÜÊ¹ÓÃµÄ»úÆ÷£¬ÔÙ½øÐÐµ÷Õû
//		// Ëó¹þÊÇÒ»ÖÖÒÕÊõ
//		for (int user_idx = 0; user_idx < client_num; user_idx++) {
//			if (need[user_idx] == 0)continue;
//			bool flag = false;
//			for(auto st : G[user_idx])
//				if (popular_site.count(st))
//				{
//					flag = true;
//					site_load[st] -= need[user_idx];
//					distri[st][user_idx] += need[user_idx];
//					break;
//				}
//			if (!flag) {
//				site_load[G[user_idx][0]] -= need[user_idx];
//				distri[G[user_idx][0]][user_idx] += need[user_idx];
//			}
//			/*int useable_site = G[user_idx].size();
//			int average = need[user_idx] / useable_site;
//			for (auto st : G[user_idx]) {
//				site_load[st] -= average;
//				distri[st][user_idx] += average;
//			}
//			site_load[G[user_idx].back()] -= need[user_idx] % useable_site;
//			distri[G[user_idx].back()][user_idx] += need[user_idx] % useable_site;*/
//		}
//		vector<int> path;
//		for (int i = 0; i < site_num; ) {
//			int site_id = i + site_offset;
//			if (site_load[site_id] < 0) {// ¶ÔÓÚ·ÖÅä³¬±êµÄ£¬ÕÒµ½ÆäËû·þÎñÆ÷½øÐÐ·ÖÅä
//				memset(vis, 0, sizeof vis);
//				path.clear();
//				cout << "some site full\n";
//				dfs(site_id, path, 1000000000, true);
//			}
//			else {
//				++i;
//			}
//
//			// ¼¦¶ùÓÃÃ»ÓÐ
//			/*else {
//				if (!popular_site.count(site_id)) {
//					for (int t = 0; t < 2000; ++t) {
//						memset(vis, 0, sizeof vis);
//						path.clear();
//						if (!dfs(site_id, path, 1000000000, false)) {
//							cout << t << "times of all\n";
//							break;
//						}
//					}
//				}
//				++i;
//			}*/
//			
//		}
//		
//		vector<int> counter(client_num);
//		string outstr;
//		for (int i = client_offset; i < client_offset + client_num; ++i) {
//			outstr += (clients[i] + ':');
//			for (int j = site_offset; j < site_offset + site_num; ++j) {
//				if (distri[j][i] > 0) {
//					if (outstr.back() != ':')
//						outstr.push_back(',');
//					outstr += ('<' + sites[j - site_offset] + ',' + to_string(distri[j][i]) +  '>');
//				}
//			}
//			outstr.push_back('\n');
//			out << outstr;
//			outstr.clear();
//		}
//#ifdef CHECKANS
//		// ¼ì²é´ð°¸ÊÇ·ñÕýÈ·
//		bool right = true;
//		for (int j = site_offset; j < site_offset + site_num; ++j) {
//			int cnt = 0;
//			for (int i = client_offset; i < client_offset + client_num; ++i) {
//				//cout << distri[j][i] << ' ';
//				cnt += distri[j][i];
//				counter[i] += distri[j][i];
//			}
//			if (cnt > sites_flow[j - site_offset])
//				right = false;
//			//cout << endl;
//		}
//		for (int i = 0; i < client_num; ++i)if (counter[i] != need[i]) right = false;
//		if (right)cout << "true\n";
//		else {
//			throw exception();
//		}
//		//cout << endl << endl;
//#endif // TEST
//
//	}
//
//	/*for (int step = 0; step < needs.size(); ++step) {
//
//	}*/
//
//}

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<cstring>
#include<fstream>
#include<functional>
#include<utility>
#include<exception>
#include<unordered_set>
#include<unordered_map>
#define TEST
#define CHECKANS
using namespace std;
using ll = long long;

ll sum_all[300];
int rank[300];
int distri[300][150]; // ÏÈ»úÆ÷ ºóÓÃ»§¶àÉÙ
int site_load[300];
int vis[300];
int fa[300];
int father(int x) {
	return x == fa[x] ? x : fa[x] = father(fa[x]);
}

int main() {
#ifdef TEST
	string prefix = "C:\\Users\\LiNing\\Desktop\\ÏßÏÂµ÷ÊÔÊý¾Ý\\data\\";
#else
	string prefix = "/data/";
#endif // TEST

	cin.tie(0);
	cout.tie(0);
	for (int i = 0; i < 300; ++i)fa[i] = i;
	ifstream fin(prefix + "demand.csv");
	string line;
	vector<string> clients;
	vector<vector<int>> needs;
	unordered_map<string, int> clientname2idx;
	fin >> line;
	for (int i = 0, j = 0; i < line.size();) {
		while (j < line.size() && line[j] != ',')++j;
		if (i != 0) {
			clients.push_back(line.substr(i, j - i));
			clientname2idx[clients.back()] = clients.size() - 1;
		}
		i = j + 1;
		j = i;
	}

	while (fin >> line) {
		vector<int> need;
		for (int i = 0, j = 0; i < line.size();) {
			while (j < line.size() && line[j] != ',')++j;
			if (i != 0) {
				need.push_back(stoi(line.substr(i, j - i)));
			}
			i = j + 1;
			j = i;
		}
		needs.push_back(need);
	}
	cout << "demand readed\n";

	vector<string> sites;
	vector<int> sites_flow;
	vector<pair<int, int>> du_of_site;
	ifstream fin_siteinfo(prefix + "site_bandwidth.csv");
	unordered_map<string, int> sitename2idx;
	fin_siteinfo >> line;
	while (fin_siteinfo >> line) {
		int dot = line.find_first_of(',');
		sites.push_back(line.substr(0, dot));
		sitename2idx[sites.back()] = sites.size() - 1;
		sites_flow.push_back(stoi(line.substr(dot + 1)));
	}
	for (int i = 0; i < sites.size(); ++i)du_of_site.push_back({ 0, i }); // {du, site}
	cout << "site info readed\n";

	ifstream fin_config(prefix + "config.ini");
	fin_config >> line >> line;
	int constraint = stoi(line.substr(line.find_first_of('=') + 1));
	cout << "constraint readed\n";

	int client_num = clients.size(), site_num = sites.size();
	int client_offset = 0, site_offset = client_num;
	vector<vector<int>> valid(site_num, vector<int>(client_num));
	vector<vector<int>> G(client_num + site_num);

	ifstream fin_qos(prefix + "qos.csv");
	fin_qos >> line;
	vector<int> cltid;
	for (int i = 0, j = 0; i < line.size();) {
		while (j < line.size() && line[j] != ',')++j;
		if (i != 0) {
			cltid.push_back(clientname2idx[line.substr(i, j - i)]);
		}
		i = j + 1;
		j = i;
	}
	int row = 0;
	while (fin_qos >> line) {
		int cur_siteid = -1;
		for (int i = 0, j = 0, col = 0; i < line.size();) {
			while (j < line.size() && line[j] != ',')++j;
			if (i != 0) {
				int qos = stoi(line.substr(i, j - i));
				int cur_cltid = cltid[col];
				if (qos < constraint) {
					du_of_site[cur_siteid].first += 1;
					valid[cur_siteid][cur_cltid] = 1;
					G[site_offset + cur_siteid].push_back(cur_cltid);
					G[cur_cltid].push_back(site_offset + cur_siteid);
				}
				++col;
			}
			else {
				cur_siteid = sitename2idx[line.substr(i, j - i)];
			}
			i = j + 1;
			j = i;
		}
		++row;
	}
	cout << "qos readed\n";
	for (int i = 0; i < client_num; i++) {
		sort(G[i].begin(), G[i].end(), [&](int a, int b) {
			return du_of_site[a - site_offset] > du_of_site[b - site_offset];
		});
	}
	sort(du_of_site.begin(), du_of_site.end());
	reverse(du_of_site.begin(), du_of_site.end());


	int topk = sites.size() / 5;
	unordered_set<int> popular_site;
	for (int i = 0; i < topk; ++i) popular_site.insert(du_of_site[i].second + site_offset);

	function<bool(int, vector<int>&, int, bool) > dfs = [&](int st, vector<int>& pth, int minval, bool urgent) {
		if (vis[st])return false;
		pth.push_back(st);
		vis[st] = 1;
		if (st >= site_offset && site_load[st] > 0 && (urgent || (!urgent && popular_site.count(st)))) {// ÕÒµ½¿ÉÒÔ×ªÒÆµÄÎ»ÖÃ
			int load = min(minval, site_load[st]);// ×ªÒÆÁ¿
			// ÐÞ¸ÄÕâÌõÂ·¾¶ÉÏµÄÖµ
			site_load[pth[0]] += load;

			// ¶ÔÓÚÂ·¾¶ÖÐ¼äµÄ½Úµã£¬ËüµÄ¸ºÔØÓ¦¸Ã²»±ä£¬Ö»ÊÇÂ·¹ý¶øÒÑ
			for (int i = 1, j = pth.size(); i < j; i += 2) {
				distri[pth[i - 1]][pth[i]] -= load;
				distri[pth[i + 1]][pth[i]] += load;
			}

			site_load[st] -= load;
			return true;
		}
		else {// ¼ÌÐøËÑË÷ÄÜ¹»°²·ÅµÄµØ·½
			for (auto next : G[st]) {
				if (next >= site_offset) {// ´ÓÏÂµ½ÉÏ£¬ nextÎª·þÎñÆ÷,ÕâÀï¶Ô·ÖÅäÁ¿¾ÍÃ»ÓÐÒªÇó
					if (!vis[next]) {
						if (dfs(next, pth, minval, urgent))
							return true;
					}
				}
				else {// ´ÓÉÏµ½ÏÂ, stÎª·þÎñÆ÷£¬±íÊ¾ÕâÌõ·ÖÅä±ß½«Òª¼õÉÙ£¬´óÓÚ0
					if (distri[st][next] > 0) {
						if (dfs(next, pth, min(distri[st][next], minval), urgent))
							return true;
					}
				}
			}
		}
		vis[st] = 0;
		pth.pop_back();
		return false;
	};
#ifdef TEST
	ofstream out("./temp.txt"); // TODO change  /output/solution.txt
#else
	ofstream out("/output/solution.txt"); // TODO change  
#endif // TEST
	for (auto need : needs) {
		for (int i = 0; i < site_num; ++i)site_load[i + site_offset] = sites_flow[i];
		memset(distri, 0, sizeof distri);
		// Ã¿¸öÓÃ»§µÄÐèÇó´óÐ¡£¬ÏÈÆ½¾ùµÄ·ÖÅä¸øËüÄÜÊ¹ÓÃµÄ»úÆ÷£¬ÔÙ½øÐÐµ÷Õû
		// Ëó¹þÊÇÒ»ÖÖÒÕÊõ
		for (int user_idx = 0; user_idx < client_num; user_idx++) {
			if (need[user_idx] == 0)continue;
			bool flag = false;
			// for(auto st : G[user_idx])
			// 	if (popular_site.count(st))
			// 	{
			// 		flag = true;
			// 		site_load[st] -= need[user_idx];
			// 		distri[st][user_idx] += need[user_idx];
			// 		break;
			// 	}
			if (!flag) {
				site_load[G[user_idx][0]] -= need[user_idx];
				distri[G[user_idx][0]][user_idx] += need[user_idx];
			}
			/*int useable_site = G[user_idx].size();
			int average = need[user_idx] / useable_site;
			for (auto st : G[user_idx]) {
				site_load[st] -= average;
				distri[st][user_idx] += average;
			}
			site_load[G[user_idx].back()] -= need[user_idx] % useable_site;
			distri[G[user_idx].back()][user_idx] += need[user_idx] % useable_site;*/
		}
		vector<int> path;
		for (int i = 0; i < site_num; ) {
			int site_id = i + site_offset;
			if (site_load[site_id] < 0) {// ¶ÔÓÚ·ÖÅä³¬±êµÄ£¬ÕÒµ½ÆäËû·þÎñÆ÷½øÐÐ·ÖÅä
				memset(vis, 0, sizeof vis);
				path.clear();
				cout << "some site full\n";
				dfs(site_id, path, 1000000000, true);
			}
			else {
				++i;
			}

			// ¼¦¶ùÓÃÃ»ÓÐ
			/*else {
				if (!popular_site.count(site_id)) {
					for (int t = 0; t < 2000; ++t) {
						memset(vis, 0, sizeof vis);
						path.clear();
						if (!dfs(site_id, path, 1000000000, false)) {
							cout << t << "times of all\n";
							break;
						}
					}
				}
				++i;
			}*/

		}

		vector<int> counter(client_num);
		string outstr;
		for (int i = client_offset; i < client_offset + client_num; ++i) {
			outstr += (clients[i] + ':');
			for (int j = site_offset; j < site_offset + site_num; ++j) {
				if (distri[j][i] > 0) {
					if (outstr.back() != ':')
						outstr.push_back(',');
					outstr += ('<' + sites[j - site_offset] + ',' + to_string(distri[j][i]) + '>');
				}
			}
			outstr.push_back('\n');
			out << outstr;
			outstr.clear();
		}
#ifdef CHECKANS
		// ¼ì²é´ð°¸ÊÇ·ñÕýÈ·
		bool right = true;
		for (int j = site_offset; j < site_offset + site_num; ++j) {
			int cnt = 0;
			for (int i = client_offset; i < client_offset + client_num; ++i) {
				//cout << distri[j][i] << ' ';
				cnt += distri[j][i];
				counter[i] += distri[j][i];
			}
			if (cnt > sites_flow[j - site_offset])
				right = false;
			//cout << endl;
		}
		for (int i = 0; i < client_num; ++i)if (counter[i] != need[i]) right = false;
		if (right)cout << "true\n";
		else {
			throw exception();
		}
		//cout << endl << endl;
#endif // TEST

	}

	/*for (int step = 0; step < needs.size(); ++step) {

	}*/

}