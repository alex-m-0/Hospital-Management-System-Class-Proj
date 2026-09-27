
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <filesystem>

using namespace std;

class Surgeon {
    string name;
public:
    Surgeon()
    {
        name = "Harry";
    }

    string getName()
    {
        return name;
    }
    Surgeon(string n)
    {
        name = n;
    }
    ~Surgeon()
    {

    }

    friend class Team;
};
class Surgery {
    string surgeryType;
    int difficulty;
    int minutes;
    string SurgeryDate;
public:
    Surgery* next;

    string getSurgeryType()
    {
        return surgeryType;
    }
    int getDifficulty()
    {
        return difficulty;
    }
    int getMinutes()
    {
        return minutes;
    }
    string getDate()
    {
        return SurgeryDate;
    }
    Surgery(string SurgeryDone, int hardness)
    {
        surgeryType = SurgeryDone;
        difficulty = hardness;

    }
    Surgery(string SurgeryDone, int hardness, int timeItTook)
    {
        surgeryType = SurgeryDone;
        difficulty = hardness;
        minutes = timeItTook;
    }
    Surgery(string SurgeryDone, int hardness, int timeItTook, string SurgeryData)
    {
        surgeryType = SurgeryDone;
        difficulty = hardness;
        minutes = timeItTook;
        SurgeryDate = SurgeryData;
    }
    Surgery()
    {

    }
    ~Surgery()
    {

    }
    friend class TeamResume;
    friend class Team;
    //friend class Hospital;
};
class Iterator {
private:
    Surgery* ptr;
public:
    Iterator(Surgery* p)
    {
        ptr = p->next;
    }

    Iterator& operator++() {
        ptr = ptr->next;
        return *this;
    }

    bool operator !=(const Iterator& other) const {
        return ptr != other.ptr;
    }

    Surgery* operator*() const {
        return ptr;
    }
};
class TeamResume {
public:
    Surgery* first;
    Surgery* lastCompleted;

    TeamResume()
    {
        first = NULL;
        lastCompleted = NULL;
    }
    void addToResume(Surgery* surg)
    {

        if (first == NULL)
        {
            first = surg;
            lastCompleted = surg;
            surg->next = NULL;
        }
        else {
            lastCompleted->next = surg;
            lastCompleted = surg;
            surg->next = NULL;
        }
    }
    void printResume()
    {
        if (first == NULL)
        {
            cout << "No surgeries in team resume." << endl;
            return;
        }
        int line = 1;
        Surgery* s;
        s = first;
        while (s != NULL)
        {
            cout << line << ")Resume item: " << s->getSurgeryType() << " Completed on: " << s->getDate() << endl;
            s = s->next;
        }
        cout << "This team averages " << AvgNumPointsPerHour() << "per hour" << endl;

    }
    double AvgNumPointsPerHour() const
    {
        double output = 0;
        double times = 0;
        if (first == NULL)
        {
            return output;
        }
        Surgery* s;
        s = first;

        while (s != NULL)
        {
            times = times + s->getMinutes();
            output = output + s->getDifficulty();
            s = s->next;
        }

        output = output / (times / 60);
        return output;
    }
    int length()
    {
        int result = 0;
        Surgery* s;
        s = first;
        while (s != NULL)
        {
            result++;
            s = s->next;
        }
        return result;
    }
    Surgery* getNthSurgery(int n)
    {
        int i = 0;
        Surgery* cursor = first;
        while (i != n) {
            cursor = cursor->next;
            i++;
        }
        return cursor;
    }
    friend class Team;

};
class Team {
public:
    vector<Surgeon> team;
    TeamResume resume;
    string TeamName;
    int resumeCount;
public:
    Team(const vector <Surgeon>& t)
    {
        team = t;
        resume = TeamResume();
        TeamName = "Anaesthesiologists";
        resumeCount = 0;
    }
    Team(const vector <Surgeon>& t, string Tname)
    {
        team = t;
        resume = TeamResume();
        TeamName = Tname;
        resumeCount = 0;
    }
    Team(string Tname)
    {
        resume = TeamResume();
        TeamName = Tname;
        resumeCount = 0;
    }

    ~Team()
    {

    }
    string getTeamName()
    {
        return TeamName;
    }
    void setTeamName(string tmnm)
    {
        TeamName = tmnm;
    }
    void addSurgeon(Surgeon sgn)
    {
        team.push_back(sgn);
    }
    Team& operator*()
    {
        return *this;
    }
    //removes the last surgeon on this list
    void removeSurgeon()
    {
        team.pop_back();
    }
    //remove specific surgeon
    void removeSurgeon(string Sname)
    {
        for (int i = 0; i < team.size(); i++)
        {
            Surgeon temp = team[i];

            if (temp.getName().compare(Sname) == 0)
            {
                team.erase(team.begin() + i);
                return;
            }

        }
        cout << "No such surgeon found on team" << endl;
    }
    Surgery* getSurgery(int n)
    {
        return resume.getNthSurgery(n);
       
    }
    void addSurgeryPerformedByTeam(Surgery* surg)
    {
        //cout<<"BOO addSurgeryPerformedByTeam()    "<<surg->getSurgeryType()<<endl;
        resume.addToResume(surg);
        resumeCount++;
    }
    void printTeamResume()
    {
        cout << "I am home" << endl;
        resume.printResume();
    }
    void printTeamMembers()
    {
        for (int i = 0; i < team.size(); i++)
        {
            cout << "Team Members are " << team[i].getName() << endl;
        }
    }
    int ResumeLength()
    {
        return resumeCount;
    }
    int TeamPtsPerHour()
    {
        cout << "resume.AvgNumPointsPerHour(); " << resume.AvgNumPointsPerHour() << endl;
        return resume.AvgNumPointsPerHour();
    }
    friend class Hospital;
};


enum SurgeryType {
    Arm,
    Heart,
    Neurological,
    Spine,
    Orthopedic
};

class SurgeryTeam {
public:
    int id;
    double averageTime;
    vector<double> surgeryDurations;

    SurgeryTeam(int id) : id(id), averageTime(0.0) {}

    void addSurgery(double duration) {
        surgeryDurations.push_back(duration);
    }

    void calculateAverageTime() {
        double totalDuration = 0.0;
        for (double duration : surgeryDurations) {
            totalDuration += duration;
        }
        averageTime = totalDuration / surgeryDurations.size();
    }

    double getAverageTime() const {
        return averageTime;
    }
};

class Hospital {
public:
    vector<Team> tems;
    TeamResume list;
    int surgs = 0;
    Hospital(const vector <Team>& t) {
        tems = t;
        list = TeamResume();
    }
    Hospital() {
        list = TeamResume();
    }

    void addTeam(Team t)
    {
        tems.push_back(t);
    }
    void removeTeam()
    {
        tems.erase(tems.begin());
    }
    void removeTeam(string name) {
        for (int i = 0; i < tems.size(); i++)
        {
            Team temp = tems[i];
            if (temp.getTeamName().compare(name) == 0)
            {
                tems.erase(tems.begin() + i);
            }
        }
    }
    void Printtems() {
        int i = 0;

        for (i = 0; i < tems.size(); i++)
        {
            Team t = tems[i];
            cout << t.getTeamName() << endl;
        }
    }

    void addSurgery(Surgery* s, string name) {
        for (int i = 0; i < tems.size(); i++) {
            if (tems[i].getTeamName() == name) {
                tems[i].addSurgeryPerformedByTeam(s);
                break; // stop searching once we've found the team
            }
        }
    }
    int TeamPts(Team& t)
    {
        int pts = t.TeamPtsPerHour();
        return pts;
    }
    void displaySurgeries(string const StartDate, string endDate)
    {
        string str = StartDate;
        string str2 = endDate;

        int StartDD = StringToInt(getDate(StartDate));
        int StartMM = StringToInt(getMonth(StartDate));
        int StartYYYY = StringToInt(getYear(StartDate));

        int ENDDD = StringToInt(getDate(endDate));
        int ENDMM = StringToInt(getMonth(endDate));
        int ENDYYYY = StringToInt(getYear(endDate));

        vector <Surgery> surgeries;

        for (int i = 0; i < tems.size(); i++)
        {
            Team t = tems[i];
            for (int j = 0; j < t.ResumeLength(); j++)
            {
                Surgery* s = t.resume.getNthSurgery(j);
                if (CheckSurgery(StartDate, endDate, s)) {

                    cout << "Team " << t.getTeamName() << " Completed a surgery on " << s->getDate() << " and it was a " << s->getSurgeryType() << endl;
                }
            }
        }
    }
    void displaySurgeries()//displays all surgeries on list
    {
        list.printResume();
    }
    void displaySurgeries(Team t)//displays all surgeries on a TEAM
    {
        t.printTeamResume();
    }
    string getMonth(string const Date)
    {
        string str = Date;
        string temp = str;
        int posOfSlash = temp.find_first_of('/');
        temp = str.substr(posOfSlash + 1, str.length()); //we have DD/YYYY

        string temp2 = str.substr(0, posOfSlash); //We have MM
        //cout<<temp2<<endl;
        return temp2;
    }
    string getDate(string const Date)
    {
        string str = Date;
        string temp = str;
        int posOfSlash = temp.find_first_of('/');
        temp = str.substr(posOfSlash + 1, str.length()); //we have DD/YYYY

        string temp2 = str.substr(0, posOfSlash); //We have MM

        int posOfSlash2 = temp.find_first_of('/');
        string temp3 = temp.substr(0, posOfSlash2);//DD retrieved
        return temp3;
    }
    string getYear(string const Date)
    {
        string str = Date;
        //get date day
        string temp = str;
        int posOfSlash = temp.find_first_of('/');
        temp = str.substr(posOfSlash + 1, str.length()); //we have DD/YYYY

        string temp2 = str.substr(0, posOfSlash); //We have MM

        int posOfSlash2 = temp.find_first_of('/');
        string temp3 = temp.substr(0, posOfSlash2);//DD retrieved

        str = temp.substr(posOfSlash2 + 1, temp.length()); // YYYY retrieved
        return str;
    }
    //decode string assumes only numbers are entered
    int StringToInt(string num)
    {
        int result = 0;
        int max = num.length();
        for (int i = 0; i < num.length(); i++)
        {
            max--;
            result = CharToInt(num[i]) * (pow(10, max)) + result;
        }
        return result;
    }
    int getListLength()
    {
        cout << list.length() << endl;
        return list.length();
    }
    int CharToInt(char c)
    {
        if (c == '0')
            return 0;
        else if (c == '1')
            return 1;
        else if (c == '2')
            return 2;
        else if (c == '3')
            return 3;
        else if (c == '4')
            return 4;
        else if (c == '5')
            return 5;
        else if (c == '6')
            return 6;
        else if (c == '7')
            return 7;
        else if (c == '8')
            return 8;
        else if (c == '9')
            return 9;
        return -1;
    }

    void addSurgeryToTeam(Team& t, Surgery* s)
    {
        t.addSurgeryPerformedByTeam(s);
        list.addToResume(s);
        surgs++;
    }
    void printTeamResume(Team& t)
    {
        t.printTeamResume();
    }
    Team& getTeam(int i)
    {
        return tems.at(i);
    }

    bool CheckSurgery(string startDate, string endDate, Surgery* s)
    {
        string date = s->getDate();
        int sDD = StringToInt(getDate(date));
        int sMM = StringToInt(getMonth(date));
        int sYY = StringToInt(getYear(date));

        if (sDD >= StringToInt(getDate(startDate)) && sDD <= StringToInt(getDate(endDate))) //is date DD between start and end
        {
            if (sMM >= StringToInt(getMonth(startDate)) && sMM <= StringToInt(getMonth(endDate))) //yes it is, now is month between start and end
            {
                if (sYY >= StringToInt(getYear(startDate)) && sYY <= StringToInt(getYear(endDate))) // yes it is now we check the year
                    return true;//year was between start and end
                else
                    return false;//year was out of bounds
            }
            // no month was not in between start MM and end MM
            else {
                ////exist in case you have the case where startDates/endDates are 7/12/2004 and 1/23/2006 and the date is 3/21/2005
                if (sYY > StringToInt(getYear(startDate)) && sYY < StringToInt(getYear(endDate)))
                    return true;
                else
                    return false;
            }
        }
        //date is not in between
        else {
            if (sMM >= StringToInt(getMonth(startDate)) && sMM <= StringToInt(getMonth(endDate)))
            {
                if (sYY >= StringToInt(getYear(startDate)) && sYY <= StringToInt(getYear(endDate)))
                    return true;
                else
                    return false;
            }
            else {
                if (sYY >= StringToInt(getYear(startDate)) && sYY < StringToInt(getYear(endDate)))
                    return true;
                else
                    return false;
            }
        }
    }
   
public:
    vector<SurgeryTeam> teams;
    vector<double> difficultyCounts;
    vector<int> surgeriesPerHour;
    vector<double> expectedSurgeries;
    double capacity;

    Hospital(double capacity) : capacity(capacity) {
        difficultyCounts.resize(9, 1);
        surgeriesPerHour.resize(5, 0);
    }

    void addTeam(const SurgeryTeam& team) {
        teams.push_back(team);
    }

    void addSurgeries(SurgeryType type, int count) {
        difficultyCounts[type] += count;
        surgeriesPerHour[type] += count;
    }

    void estimateSurgeryDuration() {
        for (SurgeryTeam& team : teams) {
            double totalDuration = 0.0;
            int surgeryCount = 0;
            for (double duration : team.surgeryDurations) {
                totalDuration += duration;
                surgeryCount++;
            }
            if (surgeryCount != 0) {
                team.averageTime = totalDuration / surgeryCount;
            } else {
                // If no surgeries have been performed, assign a default value
                team.averageTime = 1.0; // Adjust as needed
            }
        }
    }

    void estimateLikelySurgeries() {
        double totalSurgeries = 0.0;
        for (double count : difficultyCounts) {
            totalSurgeries += count;
        }

        expectedSurgeries.resize(teams.size(), 0); // Resize to match the number of teams

        for (int i = 0; i < teams.size(); i++) {
            expectedSurgeries[i] = (difficultyCounts[i] / totalSurgeries) * surgeriesPerHour[i];
        }
    }

    void predictEnergyRequired() {
            for (const SurgeryTeam& team : teams) {
                double energyRequired = 0.0;

                for (int i = 0; i < expectedSurgeries.size(); i++) {
                    double surgeryCount = expectedSurgeries[i];
                    double surgeryDuration = team.getAverageTime(); // Duration for a single surgery of type i
                    double competence = 1.0 + (i * 0.005); // Competence of team increases by 0.005 with increasing teams

                    // Adjusted equation to estimate energy required
                    double energy = (difficultyCounts[i] * (surgeryDuration * competence)) / team.surgeryDurations.size();
                    energyRequired += energy;
                }

                cout << "Team " << team.id << " requires " << energyRequired << " units of energy." << endl;
            }
        }

    void distributeCapacity() {
        vector<SurgeryTeam> sortedTeams = teams;
        sort(sortedTeams.begin(), sortedTeams.end(), [](const SurgeryTeam& a, const SurgeryTeam& b) {
            return a.getAverageTime() < b.getAverageTime();
        });
        double remainingCapacity = capacity;
        double totalEnergyRequired = 0.0; // Track the total energy required by all teams

        // Iterate over each hour of the estimated power outage
        int estimatedOutageHours = 8; // Adjust as needed
        for (int hour = 0; hour < estimatedOutageHours; hour++) {
            // Iterate over surgeries in order of expected number and complexity
            for (int i = 0; i < expectedSurgeries.size(); i++) {
                int surgeryCount = expectedSurgeries[i];
                double surgeryDuration = sortedTeams[i].getAverageTime(); // Duration for a single surgery of type i

                // Check if team is available, has enough capacity, and surgery type matches
                double teamEnergy = surgeryCount * surgeryDuration;
                SurgeryType surgeryType = static_cast<SurgeryType>(i);

                if (sortedTeams[i].getAverageTime() <= remainingCapacity && totalEnergyRequired + teamEnergy <= capacity &&
                    surgeryCount > 0) {
                    // Assign the team to perform the surgery
                    cout << "Assigned team " << sortedTeams[i].id << " to perform " << surgeryTypeToString(surgeryType) << " surgery." << endl;
                    remainingCapacity -= surgeryDuration;
                    totalEnergyRequired += teamEnergy;
                    surgeryCount--;

                    // Estimate the time when the team will finish the assigned surgery
                    double finishTime = hour + surgeryDuration;
                    cout << "Team " << sortedTeams[i].id << " will finish surgery at hour " << finishTime << endl;

                    // Update the expected surgery count for the surgery type
                    expectedSurgeries[i]--;
                }
            }
        }
    }


    string surgeryTypeToString(SurgeryType type) {
        switch (type) {
            case Arm:
                return "Arm";
            case Heart:
                return "Heart";
            case Neurological:
                return "Neurological";
            case Spine:
                return "Spine";
            case Orthopedic:
                return "Orthopedic";
            default:
                return "Unknown";
        }
    }
};


int main() {

    Hospital empty;

    Hospital h1;

    Hospital h2;

    Hospital h3;

    Hospital h4;

    Hospital h5;

    string fname = "C:\\Users\\Owner\\Documents\\C++ Code\\WEEK13\\HospitalDatabase_V1.1.csv";//cahnge the datapath to your laptop

    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
    else
        cout << "Could not open the file\n";

    for (int i = 0; i < content.size(); i++)
    {
        for (int j = 0; j < content[i].size(); j++)
        {
            cout << content[i][j] << " ";
        }
        cout << "\n";
    }
   // cout << content[1][2] << endl;


    for (int i = 0; i < content.size(); i++)
    {
        string startdate;
        string surgerytime;
        string difficultylevel;
        string surgerytype;
        string hospitalname;
        string teamname;
        Surgery* s1 = NULL;
        for (int j = 0; j < content[i].size(); j++)
        {
            if (j % 8 == 0)
            {
                string startdate;
                startdate = content[i][j];
            }
            else if (j % 8 == 1)
            {
                string enddate;
                enddate = content[i][j];
            }
            else if (j % 8 == 2)
            {
                string substation;
                substation = content[i][j];
            }
            else if (j % 8 == 3)
            {
                string hospitalname;
                hospitalname = content[i][j];
            }
            else if (j % 8 == 4)
            {
                string teamname;
                teamname = content[i][j];
            }
            else if (j % 8 == 5)
            {
                string surgerytype;
                surgerytype = content[i][j];
            }
            else if (j % 8 == 6)
            {
                string surgerytime;
                surgerytime = content[i][j];
            }
            else if (j % 8 == 7)
            {
                string difficultylevel;
                difficultylevel = content[i][j];
            }
            int diff;
            diff = empty.StringToInt(difficultylevel);
            int surg;
            surg = empty.StringToInt(surgerytime);


            Surgery* s1 = new Surgery(surgerytype, diff, surg, startdate);
        }
        if ("H1" == hospitalname)
        {
            Team t = h1.tems[0];
            //checking if team exists
            for (int k = 0; k < h1.tems.size(); k++)
            {
                Team t = h1.tems[k];
                if (t.getTeamName() == teamname)
                {
                    h1.addSurgeryToTeam(t, s1);
                }

            }
        }
        if ("H2" == hospitalname)
        {
            Team t = h2.tems[0];
            //checking if team exists
            for (int k = 0; k < h1.tems.size(); k++)
            {
                Team t = h2.tems[k];
                if (t.getTeamName() == teamname)
                {
                    h2.addSurgeryToTeam(t, s1);
                }
            }
        }
        if ("H3" == hospitalname)
        {
            Team t = h3.tems[0];
            //checking if team exists
            for (int k = 0; k < h1.tems.size(); k++)
            {
                Team t = h3.tems[k];
                if (t.getTeamName() == teamname)
                {
                    h3.addSurgeryToTeam(t, s1);
                }
            }
        }
        if ("H4" == hospitalname)
        {
            Team t = h4.tems[0];
            //checking if team exists
            for (int k = 0; k < h1.tems.size(); k++)
            {
                Team t = h4.tems[k];
                if (t.getTeamName() == teamname)
                {
                    h4.addSurgeryToTeam(t, s1);
                }

            }
        }
        if ("H5" == hospitalname)
        {
            Team t = h5.tems[0];
            //checking if team exists
            for (int k = 0; k < h5.tems.size(); k++)
            {
                Team t = h5.tems[k];
                if (t.getTeamName() == teamname)
                {
                    h5.addSurgeryToTeam(t, s1);
                }

            }
            string const s = teamname;
            h5.addSurgeryToTeam(t, s1);
        }
    }
  
    h5.tems[0].printTeamResume();

    return 0;
 }
           /*
                 double capacity = 1000.0; // Initial available capacity of the hospital (example value)
                 Hospital hospital(capacity);
                 // Read data from CSV
                 string filename = "/Users/Mahadi/Documents/ESE 224/23/HospitalDatabase_V1.1.csv";
                 readDataFromCSV(filename, hospital);
                 
                 // Step 1: Estimate surgery duration
                 hospital.estimateSurgeryDuration();
                 
                 // Step 2: Estimate likely surgeries
                 hospital.difficultyCounts.resize(5, 0);
                 hospital.surgeriesPerHour.resize(5, 0);
                 hospital.addSurgeries(Arm, 5);
                 hospital.addSurgeries(Heart, 3);
                 hospital.addSurgeries(Neurological, 2);
                 hospital.addSurgeries(Spine, 4);
                 hospital.addSurgeries(Orthopedic, 5);
                 hospital.expectedSurgeries.resize(hospital.teams.size(), 0);
                 hospital.estimateLikelySurgeries();
                 
                 // Step 3: Predict energy required by each team
                 hospital.predictEnergyRequired();
                 
                 // Step 4: Distribute available capacity to maximize outcome
                 hospital.distributeCapacity();
                 */
                //return 0;
            
        
