#pragma once
#include "GeneralPattern.h"
class JsonManager
{
public:

	// GET request
	static bool sendGetMatches() {
		/*const String jsonFoldername = DateTime::Now().format(U"yyyy-MM-dd HH-mm-ss");
		const String jsonsaveFolder = U"json/" + jsonFoldername + U"/";*/

		const String token = U"token1";
		const URL url = U"localhost:8080/problem";
		const HashTable<String, String> headers = { {U"Procon-Token", token} };
		const FilePath saveFilePath = U"get_matches_response.json";

		//if GET request OK
		if (const auto response = SimpleHTTP::Get(url, headers, saveFilePath)) {
			Print << response.getStatusLine();

			if (response.isOK()) {
				const JSON json = JSON::Load(saveFilePath);
				if (not json) {
					throw Error{ U"Failed to load " + saveFilePath };
				}
			}
			else {
				return false;
			}
		}
		else { // if Get request failed
			Print << U"Failed to send getMatches.";
			return false;
		}

		return true;
	}


	// POST request
	static bool sendPostAction() {

		const URL url = U"localhost:8080/answer";
		const String token = U"token1";
		const HashTable<String, String> headers = { {U"Procon-Token", token}, {U"Content-Type", U"application/json"} };
		const FilePath saveFilePath = U"post_action_response.json";

		//preparation for json to send
		JSON sendjson = JSON::Load(U"solution.json");
		const std::string data = sendjson.formatUTF8();

		//post request to server
		if (auto response = SimpleHTTP::Post(url, headers, data.data(), data.size(), saveFilePath)) {
			Print << response.getStatusLine();

			if (response.isOK()) {
				const JSON json = JSON::Load(saveFilePath);
				if (not json) {
					throw Error{ U"Failed to load " + saveFilePath };
				}
			}
		}
		else {
			Print << U"Failed to post actions.";
		}

	}

	// JSON parse
	static std::optional<Problem> jsonParse() {
		Problem problem;

		FilePath jsonFilePath = U"get_matches_response.json";
		JSON json = JSON::Load(jsonFilePath);

		if (!json)
		{
			// JSONファイルの読み込みに失敗した場合
			Console << U"Failed to load JSON file.";
			//return std::nullopt;
			return std::nullopt;
		}
		else {
			int boardWidth = json[U"board"][U"width"].get<int>();
			int boardHeight = json[U"board"][U"height"].get<int>();
			problem.b.width = boardWidth;
			problem.b.height = boardHeight;
			//Print << U"Width: " << problem.b.width << U" Height: " << boardHeight;
			Array<String> start(boardHeight);
			Array<String> goal(boardHeight);
			
			for (int i = 0; i < boardHeight; i++) {
				start[i] = json[U"board"][U"start"][i].get<String>();
			}
			
			for (int i = 0; i < boardHeight; i++) {
				goal[i] = json[U"board"][U"goal"][i].get<String>();
			}
			problem.b.start = start;
			problem.b.goal = goal;
			//Print << U"Start board";
			/*for (int i = 0; i < boardHeight; i++) {
				Print << problem.b.start[i];
			}*/
			//Print << U"Goal board";
			/*for (int i = 0; i < boardHeight; i++) {
				Print << problem.b.goal[i];
			}*/
			int n = json[U"general"][U"n"].get<int>();
			problem.g.n = n;
			//Print << U"general patterns: " << n;
			Array<GeneralPattern> patterns;
			for (int i = 0; i < n; i++) {
				//Print << U"Pattern " << i+1 << U":";
				int h = json[U"general"][U"patterns"][i][U"height"].get<int>();
				int p = json[U"general"][U"patterns"][i][U"p"].get<int>();
				int w = json[U"general"][U"patterns"][i][U"width"].get<int>();
				
				patterns.emplace_back(p, w, h);
				/*Print << U"num: " << patterns[i].p;
				Print << U"width:" << patterns[i].width;
				Print << U"height: " << patterns[i].height;*/

				//Print << U"cells: ";
				for (int j = 0; j < h; j++) {
					patterns[i].cells[j] = json[U"general"][U"patterns"][i][U"cells"][j].get<String>();
					//Print << patterns[i].cells[j];
				}
			}

			problem.g.patterns = patterns;
			

			return problem;
		}

		
		
	}

	
};

