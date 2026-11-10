#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <cstdlib>
#include "nif.h"
#include "sort_method.h"

using namespace std;

struct ProgramOptions {
  unsigned size;
  string ord, init, name_file;
  bool trace = false, help = false;
};

void ErrorExit(const string& msg) {
  cerr << "Error: " << msg << "\nUse -h or --help for help.\n";
  exit(EXIT_FAILURE);
}

void HelpText(const string& prog) {
  cout << "Usage:\n  " << prog << " -size <n> -ord <method> -init <type> [file] -trace <true|false>\n"
       << "\nMethods: insertion | shake | quick | heap | shell"
       << "\nInit: manual | random | file [filename]"
       << "\nExample:\n  " << prog << " -size 10 -ord quick -init random -trace true\n";
}

void ParseArguments(int argc, char* argv[], ProgramOptions& opt) {
  for (int i = 1; i < argc; i += 2) {
    string arg = argv[i];
    if (arg == "-h" || arg == "--help") { opt.help = true; return; }
    if (i + 1 >= argc) ErrorExit("missing value for " + arg);
    string val = argv[i + 1];

    if (arg == "-size") opt.size = stoul(val);
    else if (arg == "-ord") opt.ord = val;
    else if (arg == "-init") {
      opt.init = val;
      if (val == "file") {
        if (i + 2 >= argc) ErrorExit("missing filename for -init file");
        opt.name_file = argv[i + 2]; ++i;
      }
    }
    else if (arg == "-trace") opt.trace = (val == "true");
    else ErrorExit("unknown argument: " + arg);
  }

  if (opt.size == 0 || opt.ord.empty() || opt.init.empty())
    ErrorExit("Missing required arguments");
}

void ManualInput(staticSequence<nif>& seq, unsigned max) {
  for (unsigned i = 0; i < max; ++i) {
    cout << "Introduce NIF #" << i + 1 << " (-1 para terminar): ";
    string s; cin >> s;
    try {
      long val = stol(s);
      if (val == -1) break;
      seq.insert(nif{val});
    } catch (...) {
      cout << "Entrada inválida.\n"; --i;
    }
  }
}

void LoadFromFile(const string& name, staticSequence<nif>& seq, unsigned max) {
  ifstream f{name};
  if (!f) ErrorExit("No se pudo abrir el archivo: " + name);
  string line; unsigned count = 0;
  while (getline(f, line) && count < max) {
    try {
      seq.insert(nif{stol(line)});
      ++count;
    } catch (...) {
      cout << "Línea inválida ignorada: " << line << '\n';
    }
  }
}

int main(int argc, char* argv[]) {
  ProgramOptions opt{};
  ParseArguments(argc, argv, opt);
  if (opt.help) { HelpText(argv[0]); return EXIT_SUCCESS; }

  staticSequence<nif> nifs(opt.size);
  if (opt.init == "random")
    for (unsigned i = 0; i < opt.size; ++i) nifs.insert(nif{});
  else if (opt.init == "manual")
    ManualInput(nifs, opt.size);
  else if (opt.init == "file")
    LoadFromFile(opt.name_file, nifs, opt.size);
  else
    ErrorExit("initialization type not recognized");

  cout << "\nAntes de ordenar:\n"; nifs.Print();

  unique_ptr<SortMethod<nif>> sorter;
  if (opt.ord == "insertion") sorter = make_unique<InsertionSort<nif>>(nifs, opt.trace);
  else if (opt.ord == "shake") sorter = make_unique<ShakerSort<nif>>(nifs, opt.trace);
  else if (opt.ord == "quick") sorter = make_unique<QuickSort<nif>>(nifs, opt.trace);
  else if (opt.ord == "heap") sorter = make_unique<HeapSort<nif>>(nifs, opt.trace);
  else if (opt.ord == "shell") sorter = make_unique<ShellSort<nif>>(nifs, opt.trace);
  else ErrorExit("sorting method not recognized");

  cout << "Ordenando con: " << opt.ord << "\n";
  sorter->sort();
  cout << "Ordenación completada.\n";

  cout << "\nDespués de ordenar:\n";
  sorter->getSeq().Print();

  return 0;
}
