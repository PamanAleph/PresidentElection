#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Candidate {
    string name;
    long int votes;

    Candidate(const string& n, long int v) : name(n), votes(v) {}
};

bool compareCandidates(const Candidate& a, const Candidate& b) {
    return a.votes > b.votes;
}

void printCandidate(const Candidate& candidate, double percentage) {
    cout << "  " << candidate.name << ": " << candidate.votes << " votes (" << percentage << "%)\n";
}

void printWinner(const Candidate& winner) {
    cout << "  Winner: " << winner.name << " (" << winner.votes << " votes)\n\n";
}

int main() {
	// Format input {Province, {{AMIN, Votes}, (PraGib, Votes), {GaMa, Votes}}}
    vector<pair<string, vector<Candidate>>> provinceVotes = {
        {"DKI Jakarta", {{"AMIN", 1919324}, {"PraGib", 1938528}, {"GaMa", 814888}}},
        {"Central Java", {{"AMIN", 2585239}, {"PraGib", 10812258}, {"GaMa", 6990942}}},
        {"East Java", {{"AMIN", 3355964}, {"PraGib", 14203356}, {"GaMa", 3821495}}},
        {"Banten", {{"AMIN", 1858797}, {"PraGib", 3091543}, {"GaMa", 545871}}},
        {"DI Yogyakarta", {{"AMIN", 385545}, {"PraGib", 1000858}, {"GaMa", 585731}}},
        {"West Java", {{"AMIN", 6831409}, {"PraGib", 12654357}, {"GaMa", 2124608}}}
    };

    for (auto& province : provinceVotes) {
        sort(province.second.begin(), province.second.end(), compareCandidates);
    }

    vector<Candidate> totalVotes;
    for (const auto& province : provinceVotes) {
        for (const auto& candidate : province.second) {
            auto it = find_if(totalVotes.begin(), totalVotes.end(), [&](const Candidate& c) {
                return c.name == candidate.name;
            });

            if (it != totalVotes.end()) {
                it->votes += candidate.votes;
            } else {
                totalVotes.push_back(candidate);
            }
        }
    }

    sort(totalVotes.begin(), totalVotes.end(), compareCandidates);

    cout << fixed << setprecision(2);

    for (const auto& province : provinceVotes) {
        cout << province.first << ":\n";
        for (const auto& candidate : province.second) {
            double percentage = (static_cast<double>(candidate.votes) / accumulate(province.second.begin(), province.second.end(), 0, [](long int sum, const Candidate& c) { return sum + c.votes; })) * 100.0;
            printCandidate(candidate, percentage);
        }
        printWinner(province.second.front());
    }

    cout << "Summary of Vote Percentages for All Provinces in Java Island:\n";
    for (const auto& candidate : totalVotes) {
        double percentage = (static_cast<double>(candidate.votes) / accumulate(totalVotes.begin(), totalVotes.end(), 0, [](long int sum, const Candidate& c) { return sum + c.votes; })) * 100.0;
        printCandidate(candidate, percentage);
    }

    return 0;
}
