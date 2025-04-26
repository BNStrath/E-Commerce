
const string csWelcome = "Welcome, are you customer or a business ? (1 / 2)\n";
const string csLoginSignup = "select:\n1.Login\n2.Sign up\n";
const string csLoginPrompt = "You may now log in\n";

void HandleBuyer(std::vector<Item*>& items, std::string& filename, Buyer& customer);

void HandleBusiness(std::vector<Item*>& items, std::string& filename, Business& business);

void GetUserResponse(string question , char& ans);

void Display(string displayString);
