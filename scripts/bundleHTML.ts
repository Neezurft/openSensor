import { readFileSync, writeFileSync } from "fs";

const INDEX_FILE = "index.html";
const ENVIRONMENT_FILE = "firmware/environment.h";

/*
  This script:

  1- Takes the contents of INDEX_FILE and converts it into a "minimised" string (no unnecessary spaces, line breaks).
  2- Takes the output of the action above and updates value of the "INDEX_HTML[]" environment variable in the ENVIRONMENT_FILE with it.
*/

const takeString = (stringText: string) => ({
  andReplaceValueBetween: (beforeText: string, afterText: string) => ({
    with: (newValue: string) =>
      stringText.replace(
        new RegExp(`(?<=${beforeText})(.*?)(?=${afterText})`),
        newValue
      ),
  }),
});

console.info(`**** Processing ${INDEX_FILE} file`);

try {
  const htmlString = readFileSync(INDEX_FILE, "utf-8")
    .replace(/\n[ ]+|\r\n|\n|\r/gm, "") // removing spaces and breaklines
    .replace(/"/gm, "'"); // escaping double quotes

  const environmentString = readFileSync(ENVIRONMENT_FILE, "utf-8");

  // updating environment variables with html string
  const newEnvironmentString = takeString(environmentString)
    .andReplaceValueBetween('INDEX_HTML\\[\\] = "', '"') // e.g. replaces VAL in: INDEX_HTML[] = "VAL";
    .with(htmlString);

  writeFileSync(ENVIRONMENT_FILE, newEnvironmentString, "utf-8");

  console.info("**** Processing complete!");
} catch (e) {
  console.error(`**** Error processing ${INDEX_FILE} file`, e);
  process.exit(1);
}
