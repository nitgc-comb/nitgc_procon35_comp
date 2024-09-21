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
	static bool jsonParse() {
		FilePath jsonFilePath = U"get_matches_response.json";
		JSON json = JSON::Load(jsonFilePath);

		if (!json)
		{
			// JSONファイルの読み込みに失敗した場合
			Console << U"Failed to load JSON file.";
			return false;
		}
		else {
			int boardWidth = json[U"board"][U"width"].get<int>();
			int boardHeight = json[U"board"][U"height"].get<int>();
			Array<String> start(boardHeight);
			for (int i = 0; i < boardHeight; i++) {
				start[i] = json[U"board"][U"start"][i].get<String>();
				Print << start[i];
			}
			Array<String> goal(boardHeight);
			for (int i = 0; i < boardHeight; i++) {
				start[i] = json[U"board"][U"goal"][i].get<String>();
				Print << goal[i];
			}
			
			int n = json[U"general"].get<int>();
			Array<GeneralPattern> patterns;
			for (int i = 0; i < n; i++) {
				patterns[i].p = json[U"general"][U"patterns"][i][U"p"].get<int>();
				patterns[i].width = json[U"general"][U"patterns"][i][U"width"].get<int>();
				patterns[i].height = json[U"general"][U"patterns"][i][U"height"].get<int>();
			
				patterns[i].cells = json[U"general"][U"patterns"][i][U"cells"].get<Array<String>>();
			}

			Print << boardWidth;
			Print << patterns[0].p;

			return true;
		}

		
		
	}

	
};

