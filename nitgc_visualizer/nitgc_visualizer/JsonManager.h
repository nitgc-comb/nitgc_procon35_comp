#pragma once
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
};

