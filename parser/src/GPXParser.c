#include "GPXParser.h"
#include "LinkedListAPI.h"

/**
 * @author Eddy Dushime | I.D : 1084994
 */

/**
 * - Used main and print_elements to build createGPXdoc function
 * with parser retrieved from http://www.xmlsoft.org/examples/tree1.c
 *
 * - Used LinkedListAPI to implement given functions
 * - Used StructListDemo to implement useful functionalities ()
 **/

//https://www.btechonline.org/2015/12/c-program-to-round-numbers-and-decimals.html
//https://rosettacode.org/wiki/Haversine_formula#C

//Total number of waypoints in the GPX file
int getNumWaypoints(const GPXdoc* doc){
    if(doc == NULL){
        return 0;
    }

    if(doc->waypoints == NULL){
        return 0;
    }

    return getLength(doc->waypoints);
}

//Total number of routes in the GPX file
int getNumRoutes(const GPXdoc* doc){
    if(doc == NULL){
        return 0;
    }

    if(doc->routes == NULL){
        return 0;
    }
    return getLength(doc->routes);
}

//Total number of tracks in the GPX file
int getNumTracks(const GPXdoc* doc){
    if(doc == NULL){
        return 0;
    }
    if(doc->tracks == NULL){
        return 0;
    }
    return getLength(doc->tracks);
}

//Total number of segments in all tracks in the document
int getNumSegments(const GPXdoc* doc){
    if(doc == NULL){
        return 0;
    }
    if(doc->tracks == NULL){
        return 0;
    }

    int count = 0;
    ListIterator iter = createIterator(doc->tracks);

    /*
    * Traverse the list using an iterator.
    * nextElement() returns NULL ones we reach the end of the list
    */
    void* cur_track = NULL;
    while ((cur_track = nextElement(&iter)) != NULL){
        count += getLength(((Track *) cur_track)->segments);
    }

    return count;
}

// The number of other data in a waypoint
int wptData(List * waypoints){
    if(waypoints == NULL){
        return 0;
    }

    ListIterator iter = createIterator(waypoints);
    int count = 0;

    void * cur_wpt = NULL;

    while((cur_wpt = nextElement(&iter)) != NULL){
        count += getLength(((Waypoint *) cur_wpt)->otherData);
        if(strcmp(((Waypoint *)cur_wpt)->name, "") != 0){
            count++;
        }
    }

    return count;
}

// The number of other data in a route
int rteData(List * routes){
    if(routes == NULL){
        return 0;
    }

    ListIterator iter = createIterator(routes);
    int count = 0;

    void * cur_rte = NULL;

    while((cur_rte = nextElement(&iter)) != NULL){
        count += getLength(((Route *) cur_rte)->otherData);
        if(strcmp(((Route *) cur_rte)->name, "") != 0){
            count++;
        }
        count += wptData(((Route *) cur_rte)->waypoints);
    }

    return count;
}

// The number of other data in a segment
int segmentData(List * segments){
    if(segments == NULL){
        return 0;
    }

    ListIterator iter = createIterator(segments);
    int count = 0;

    void * cur_seg = NULL;

    while((cur_seg = nextElement(&iter)) != NULL){
        count += wptData(((TrackSegment *)cur_seg)->waypoints);
    }

    return count;
}

// The number of other data in a track
int trackData(List * tracks){
    if(tracks == NULL){
        return 0;
    }

    ListIterator iter = createIterator(tracks);
    int count = 0;

    void * cur_trk = NULL;

    while((cur_trk = nextElement(&iter)) != NULL){
        count += getLength(((Track *) cur_trk)->otherData);
        if(strcmp(((Track *) cur_trk)->name, "") != 0){
            count++;
        }
        count += segmentData(((Track *) cur_trk)->segments);
    }

    return count;
}

//Total number of GPXData elements in the document
int getNumGPXData(const GPXdoc* doc){
    if(doc == NULL){
        return 0;
    }

    return wptData(doc->waypoints) + rteData(doc->routes) + trackData(doc->tracks);
}



// Function that returns a waypoint with the given name.  If more than one exists, return the first one.
// Return NULL if the waypoint does not exist
Waypoint* getWaypoint(const GPXdoc* doc, char* name){
    if(doc == NULL || name == NULL){
        return NULL;
    }

    void * cur_wpt = NULL;
    ListIterator iter = createIterator(doc->waypoints);

    while((cur_wpt = nextElement(&iter)) != NULL){
        if (!strcmp(((Waypoint *) cur_wpt)->name, name)){
            return ((Waypoint *) cur_wpt);
        }
    }
    return NULL;
}

// Function that returns a track with the given name.  If more than one exists, return the first one.
// Return NULL if the track does not exist
Track* getTrack(const GPXdoc* doc, char* name){
    if(doc == NULL || name == NULL){
        return NULL;
    }

    void * cur_trk = NULL;
    ListIterator iter = createIterator(doc->tracks);

    while((cur_trk = nextElement(&iter)) != NULL){
        if (!strcmp(((Track *) cur_trk)->name, name)){
            return ((Track *) cur_trk);
        }
    }
    return NULL;
}

// Function that returns a route with the given name.  If more than one exists, return the first one.
// Return NULL if the route does not exist
Route* getRoute(const GPXdoc* doc, char* name){
    if(doc == NULL || name == NULL){
        return NULL;
    }

    void * cur_rte = NULL;
    ListIterator iter = createIterator(doc->routes);

    while((cur_rte = nextElement(&iter)) != NULL){
        if (!strcmp(((Route *) cur_rte)->name, name)){
            return ((Route *) cur_rte);
        }
    }
    return NULL;
}

void deleteGpxData( void* data){
    if(data != NULL){
        free((GPXData *) data);
    }
}

char* gpxDataToString( void* data){ return ""; }
int compareGpxData(const void *first, const void *second){ return 0; }

void deleteWaypoint(void* data){
    if(data != NULL){
        Waypoint * to_delete = (Waypoint *) data;
        free(to_delete->name);
        freeList(to_delete->otherData);
        free(to_delete);
    }
}

char* waypointToString( void* data){ return ""; }
int compareWaypoints(const void *first, const void *second){ return 0; }

void deleteRoute(void* data){
    if(data != NULL){
        Route * to_delete = (Route *) data;
        free(to_delete->name);
        freeList(to_delete->waypoints);
        freeList(to_delete->otherData);
        free(to_delete);
    }
}

char* routeToString(void* data){ return ""; }
int compareRoutes(const void *first, const void *second){ return 0; }

void deleteTrackSegment(void* data){
    if(data != NULL){
        TrackSegment * to_delete = (TrackSegment *) data;
        freeList(to_delete->waypoints);
        free(to_delete);
    }
}

char* trackSegmentToString(void* data){ return ""; }
int compareTrackSegments(const void *first, const void *second){ return 0; }

void deleteTrack(void* data){
    if(data != NULL){
        Track * to_delete = (Track *) data;
        free(to_delete->name);
        freeList(to_delete->segments);
        freeList(to_delete->otherData);
        free(to_delete);
    }
}

char* trackToString(void* data){ return ""; }
int compareTracks(const void *first, const void *second){ return 0; }

GPXData * initData(xmlNode * data){
    if (data != NULL){
        GPXData * new_data = malloc( sizeof(GPXData) + 256);

        if (data->type == XML_ELEMENT_NODE){
            if(data->name != NULL && data->children != NULL) {
                strcpy(new_data->name, (char *) data->name);
                strcpy(new_data->value, (char *) data->children->content);
                return new_data;
            }
        }
    }

    return NULL;
}

Waypoint * initWaypoint(xmlNode * point){
    if(point == NULL){
        return NULL;
    }

    Waypoint * new_point = malloc(sizeof(Waypoint));
    new_point->latitude = 0;
    new_point->longitude = 0;
    new_point->name = malloc(256);
    strcpy(new_point->name, "");
    new_point->otherData = initializeList(&gpxDataToString, &deleteGpxData, &compareGpxData);

    for (xmlNode * cur_node = point->children; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE){
            if(!xmlIsBlankNode(cur_node)){
                if(!strcmp("name", (char*) cur_node->name)) {
                    if(cur_node->children != NULL){
                        strcpy(new_point->name, (char *) cur_node->children->content);
                    }
                } else{
                    insertBack(new_point->otherData, initData(cur_node));
                }
            }
        }
    }

    for (xmlAttr * attributes = point->properties; attributes != NULL; attributes = attributes->next){
        if(!strcmp("lat", (char*) attributes->name)){
            new_point->latitude = strtod((char *) attributes->children->content, NULL);
        } else if(!strcmp("lon", (char*) attributes->name)){
            new_point->longitude = strtod((char *) attributes->children->content, NULL);
        }
    }

    return new_point;
}

Route * initRoute(xmlNode * route){
    if(route == NULL){
        return NULL;
    }

    Route * new_route = malloc(sizeof(Route));
    new_route->name = malloc(sizeof(char) * 256);
    strcpy(new_route->name, "");

    new_route->otherData = initializeList(&gpxDataToString, &deleteGpxData, &compareGpxData);
    new_route->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);

    for (xmlNode * cur_node = route->children; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE){
            if(!xmlIsBlankNode(cur_node)){
                if(!strcmp("name", (char*) cur_node->name)) {
                    if(cur_node->children != NULL){
                        strcpy(new_route->name, (char *) cur_node->children->content);
                    }
                } else if(!strcmp("rtept", (char*) cur_node->name)){
                    insertBack(new_route->waypoints, initWaypoint(cur_node));
                } else{
                    insertBack(new_route->otherData, initData(cur_node));
                }
            }
        }
    }

    return new_route;
}

TrackSegment * initSegment(xmlNode * segment){
    TrackSegment * new_segment = malloc(sizeof(TrackSegment));
    new_segment->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);

    for (xmlNode * cur_node = segment->children; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE){
            if(!strcmp("trkpt", (char*) cur_node->name)){
                insertBack(new_segment->waypoints, initWaypoint(cur_node));
            }
        }
    }
    return new_segment;
}

Track * initTrack(xmlNode * track){
    if(track == NULL){
        return NULL;
    }

    Track * new_track = malloc(sizeof(Track));
    new_track->name = malloc(256);
    strcpy(new_track->name, "");

    new_track->otherData = initializeList(&gpxDataToString, &deleteGpxData, &compareGpxData);
    new_track->segments = initializeList(&trackSegmentToString, &deleteTrackSegment, &compareTrackSegments);

    for (xmlNode * cur_node = track->children; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE){
            if(!xmlIsBlankNode(cur_node)){
                if(!strcmp("name", (char*) cur_node->name)) {
                    if(cur_node->children != NULL){
                        strcpy(new_track->name, (char *) cur_node->children->content);
                    }
                } else if(!strcmp("trkseg", (char*) cur_node->name)){
                    insertBack(new_track->segments, initSegment(cur_node)); //loss of memory, make variables to hold temporarily then free upon insert
                } else{
                    insertBack(new_track->otherData, initData(cur_node));
                }
            }
        }
    }

    return new_track;
}

/**
 * parse:
 * @a_node: the initial xml node to consider.
 * @parse_pointer: the pointer to the gpxdoc structure
 *
 * Prints the names of the all the xml elements
 * that are siblings or children of a given xml node.
 */
void parse(GPXdoc * to_parse, xmlNode * a_node){
    if(to_parse == NULL || a_node == NULL){
        return;
    }

    xmlNode * cur_node = NULL;
    xmlAttr * attributes = NULL;

    for (attributes = a_node->properties; attributes != NULL; attributes = attributes->next){
        if(!strcmp("version", (char *) attributes->name)){
            to_parse->version = strtod((char *) attributes->children->content, NULL);
        } else if(!strcmp("creator", (char *) attributes->name)){
            to_parse->creator = malloc(256); /* extra byte for null character*/
            strcpy(to_parse->creator, (char *) attributes->children->content);
        } else if(!strcmp("schemaLocation", (char *) attributes->name)){
            strcpy(to_parse->namespace, (char *) a_node->ns->href);
        }
    }

    for (cur_node = a_node->children; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            if(!strcmp((char *) cur_node->name, "wpt")){
                insertBack(to_parse->waypoints, initWaypoint(cur_node));
            } else if(!strcmp((char *) cur_node->name, "rte")){
                insertBack(to_parse->routes, initRoute(cur_node));
            } else if(!strcmp((char *) cur_node->name, "trk")){
                insertBack(to_parse->tracks, initTrack(cur_node));
            }
        }
    }
}


// Function that converts an GPXdoc waypoints into xmlDoc struct elements
void dataToxml(List * data, xmlNodePtr node){
    if(data == NULL || getLength(data) < 1){
        return;
    }

    GPXData * cur_data = NULL;
    xmlNodePtr element  = NULL;
    xmlNodePtr node_value  = NULL;
    ListIterator iter = createIterator(data);

    while((cur_data = nextElement(&iter)) != NULL){
        element = xmlNewNode(node->ns, BAD_CAST cur_data->name);
        node_value = xmlNewText(BAD_CAST cur_data->value);

        xmlAddChild(element, node_value);
        xmlAddChild(node, element);
    }
}

// Function that converts an GPXdoc waypoints into xmlDoc struct elements
void waypointToxml(List * waypoints, xmlNodePtr node, char * type){
    if(waypoints == NULL || getLength(waypoints) < 1){
        return;
    }

    char latitude[256];
    char longitude[256];
    Waypoint * cur_wpt = NULL;
    xmlNodePtr waypoint  = NULL;
    ListIterator iter = createIterator(waypoints);

    while((cur_wpt = nextElement(&iter)) != NULL){
        waypoint  = xmlNewChild(node, node->ns, BAD_CAST type, NULL);

        sprintf(latitude, "%f", cur_wpt->latitude);
        sprintf(longitude, "%f", cur_wpt->longitude);
        xmlNewProp(waypoint, BAD_CAST "lat", BAD_CAST latitude);
        xmlNewProp(waypoint, BAD_CAST "lon", BAD_CAST longitude);

        if(strcmp(cur_wpt->name, "") != 0){
            xmlNewChild(waypoint, node->ns, BAD_CAST "name", BAD_CAST cur_wpt->name);
        }
        dataToxml(cur_wpt->otherData, waypoint);
    }
}

// Function that converts an GPXdoc waypoints into xmlDoc struct elements
void routeToxml(List * routes, xmlNodePtr root){
    if(routes == NULL || getLength(routes) < 1){
        return;
    }

    Route * cur_rte = NULL;
    xmlNodePtr route  = NULL;
    ListIterator iter = createIterator(routes);

    while((cur_rte = nextElement(&iter)) != NULL){
        route  = xmlNewChild(root, root->ns, BAD_CAST "rte", NULL);

        if(strcmp(cur_rte->name, "") != 0){
            xmlNewChild(route, root->ns, BAD_CAST "name", BAD_CAST cur_rte->name);
        }
        dataToxml(cur_rte->otherData, route);
        waypointToxml(cur_rte->waypoints, route, "rtept");
    }
}


// Function that converts an GPXdoc waypoints into xmlDoc struct elements
void trackSegToxml(List * segments, xmlNodePtr node){
    if(segments == NULL || getLength(segments) < 1){
        return;
    }

    TrackSegment * cur_trkseg = NULL;
    xmlNodePtr segment  = NULL;
    ListIterator iter = createIterator(segments);

    while((cur_trkseg = nextElement(&iter)) != NULL){
        segment  = xmlNewChild(node, node->ns, BAD_CAST "trkseg", NULL);
        waypointToxml(cur_trkseg->waypoints, segment, "trkpt");
    }
}


// Function that converts an GPXdoc waypoints into xmlDoc struct elements
void trackToxml(List * tracks, xmlNodePtr root){
    if(tracks == NULL || getLength(tracks) < 1){
        return;
    }

    Track * cur_trk = NULL;
    xmlNodePtr track  = NULL;
    ListIterator iter = createIterator(tracks);

    while((cur_trk = nextElement(&iter)) != NULL){
        track  = xmlNewChild(root, root->ns, BAD_CAST "trk", NULL);

        if(strcmp(cur_trk->name, "") != 0){
            xmlNewChild(track, root->ns, BAD_CAST "name", BAD_CAST cur_trk->name);
        }
        dataToxml(cur_trk->otherData, track);
        trackSegToxml(cur_trk->segments, track);
    }
}

// Function that converts an GPXdoc into an xmlDoc struct, i.e. a libxml tree.
xmlDocPtr convertToxml(GPXdoc * document){
    if(document == NULL){
        return NULL;
    }

    xmlDocPtr xmlDoc = NULL;        /* document pointer */
    xmlNodePtr root_node = NULL;    /* node pointers */

    LIBXML_TEST_VERSION;

    /*
     * Creates a new document, a node and set it as a root node
     */
    char version[4];
    xmlDoc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST "gpx");
    xmlNsPtr space = xmlNewNs(root_node, BAD_CAST document->namespace, NULL);
    xmlSetNs(root_node, space);

    sprintf(version, "%.1f", document->version);
    xmlNewProp(root_node, BAD_CAST "version", BAD_CAST version);
    xmlNewProp(root_node, BAD_CAST "creator", BAD_CAST document->creator);

    waypointToxml(document->waypoints, root_node, "wpt");
    routeToxml(document->routes, root_node);
    trackToxml(document->tracks, root_node);
    xmlDocSetRootElement(xmlDoc, root_node);

    return xmlDoc;
}

//xmllint --noout --schema test.xsd test.xml <- linux

// Function that validates a libxml tree based on a xsd file
bool schema_valid(xmlDocPtr xmlDoc, char * XSDFileName ){
    if (xmlDoc == NULL){
        return false;
    }

    int result = -1;
    bool output = false;
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt = xmlSchemaNewParserCtxt(XSDFileName);

    //schema ctxt
    xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
    schema = xmlSchemaParse(ctxt);
    xmlSchemaFreeParserCtxt(ctxt);

    //compare to schema ctxt
    xmlSchemaValidCtxtPtr ctxt_2 = xmlSchemaNewValidCtxt(schema);
    xmlSchemaSetValidErrors(ctxt_2, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
    result = xmlSchemaValidateDoc(ctxt_2, xmlDoc);

    if (result == 0){
        output  = true;
    } else{
        output = false;
    }

    xmlSchemaFreeValidCtxt(ctxt_2);

    // free the resource
    if(schema != NULL){
        xmlSchemaFree(schema);
    }

    return output;
}

// Function to validate data
bool data_valid(List * list){
    if(list == NULL){
        return false;
    }

    if(getLength(list) < 1){
        return true;
    }

    bool output = true;
    GPXData * current = NULL;
    ListIterator iter = createIterator(list);

    while((current = nextElement(&iter)) != NULL){
        if(current->name == NULL || strcmp(current->name, "") == 0){
            return false;
        }
        if(current->value == NULL || strcmp(current->value, "") == 0){
            return false;
        }
    }
    return output;
}

// Function to validate waypoints
bool waypoints_valid(List * list){
    if(list == NULL){
        return false;
    }

    if(getLength(list) < 1){
        return true;
    }

    bool output = true;
    Waypoint * current = NULL;
    ListIterator iter = createIterator(list);

    while((current = nextElement(&iter)) != NULL){
        if(current->name == NULL){
            return false;
        }
        output = data_valid(current->otherData);
    }
    return output;
}

// Function to validate segments
bool segments_valid(List * list){
    if(list == NULL){
        return false;
    }

    if(getLength(list) < 1){
        return true;
    }

    bool output = true;
    TrackSegment * current = NULL;
    ListIterator iter = createIterator(list);

    while((current = nextElement(&iter)) != NULL){
        output = waypoints_valid(current->waypoints);
    }
    return output;
}

// Function to validate routes
bool routes_valid(List * list){
    if(getLength(list) < 1){
        return true;
    }

    bool output = true;
    Route * current = NULL;
    ListIterator iter = createIterator(list);

    while((current = nextElement(&iter)) != NULL){
        if(current->name == NULL){
            return false;
        }
        output = waypoints_valid(current->waypoints);
        output = data_valid(current->otherData);
    }
    return output;
}

// Function to validate tracks
bool tracks_valid(List * list){
    if(getLength(list) < 1){
        return true;
    }

    bool output = true;
    Track * current = NULL;
    ListIterator iter = createIterator(list);

    while((current = nextElement(&iter)) != NULL){
        if(current->name == NULL){
            return false;
        }
        output = segments_valid(current->segments);
        output = data_valid(current->otherData);
    }
    return output;
}

// Function that validates a lists of wpts, rtes and trks
bool lists_valid(GPXdoc * doc){
    bool output = true;

    output = waypoints_valid(doc->waypoints);
    output = routes_valid(doc->routes);
    output = tracks_valid(doc->tracks);

    return output;
}

// Function that validates a GPXdoc based on restricitons
bool xml_valid(GPXdoc * doc){
    if(doc == NULL){
        return false;
    }

    if((doc->namespace == NULL) || strcmp(doc->namespace, "") == 0){
        return false;
    }

    if(doc->creator == NULL || strcmp(doc->creator, "") == 0){
        return false;
    }

    if(doc->waypoints == NULL || doc->routes == NULL || doc->tracks == NULL){
        return false;
    }
    return lists_valid(doc);
}

/** Function to create an GPX object based on the contents of an GPX file.
 *@pre File name cannot be an empty string or NULL.
       File represented by this name must exist and must be readable.
 *@post Either:
        A valid GPXdoc has been created and its address was returned
		or
		An error occurred, and NULL was returned
 *@return the pointer to the new struct or NULL
 *@param fileName - a string containing the name of the GPX file
**/
GPXdoc* createGPXdoc(char* fileName){
    xmlDoc * doc = NULL;
    xmlNode * root_element = NULL;

    /*parse the file and get the DOM */
    doc = xmlReadFile(fileName, NULL, 0);

    if (doc == NULL) {
    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
        xmlCleanupParser();
        return NULL;
    }

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    GPXdoc * to_parse = malloc(sizeof(GPXdoc));


    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    to_parse->routes = initializeList(&routeToString, &deleteRoute, &compareRoutes);
    to_parse->tracks = initializeList(&trackToString, &deleteTrack, &compareTracks);
    to_parse->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);

    parse(to_parse, root_element);

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    return to_parse;
}

/** Function to delete doc content and free all the memory.
 *@pre GPX object exists, is not null, and has not been freed
 *@post GPX object had been freed
 *@return none
 *@param obj - a pointer to an GPX struct
**/
void deleteGPXdoc(GPXdoc* doc){
    if(doc != NULL){
        free(doc->creator);
        freeList(doc->waypoints);
        freeList(doc->routes);
        freeList(doc->tracks);
        free(doc);
    }
}

/** Function to create a string representation of an GPX object.
 *@pre GPX object exists, is not null, and is valid
 *@post GPX has not been modified in any way, and a string representing the GPX contents has been created
 *@return a string contaning a humanly readable representation of an GPX object
 *@param obj - a pointer to an GPX struct
**/
char* GPXdocToString(GPXdoc* doc){
    if(doc == NULL){
        return NULL;
    }

    char * to_Print = malloc(2);
    strcpy(to_Print, "");
    //     char * waypoints = NULL;
    //     char * routes = NULL;
    //     char * tracks = NULL;

    //     /*
    //     Length of the string is:
    //     length of the first and last names+3 spaces+4 chars for "Age:"+1 character for '\0'+20 digits to represent the age
    //     While we only need 3 digits to represent the human age, if the age is uninitialised, it can be any int value
    //     An int is 4 bytes, and needs up to 20 chars to represent it
    //     If we don't do this, our code will crash if age is uninitialized
    //     */

    //     /*
    //      * REMEMBER TO FREE EVERYTIME YOU USE toString()
    //      *
    //      */

    //     len = strlen(tmpName->firstName)+strlen(tmpName->lastName)+28;
    //     tmpStr = (char*)malloc(sizeof(char)*len);

    //     sprintf(to_print, "Namespace: %s Version: %f Creator: %s", doc->namespace, doc->version, doc->creator);

    //     return to_Print;
    // }
    return to_Print;
}

/** Function to create an GPX object based on the contents of an GPX file.
 * This function must validate the XML tree generated by libxml against a GPX schema file
 * before attempting to traverse the tree and create an GPXdoc struct
 *@pre File name cannot be an empty string or NULL.
       File represented by this name must exist and must be readable.
 *@post Either:
        A valid GPXdoc has been created and its address was returned
		or
		An error occurred, and NULL was returned
 *@return the pinter to the new struct or NULL
 *@param gpxSchemaFile - the name of a schema file
 *@param fileName - a string containing the name of the GPX file
**/
GPXdoc* createValidGPXdoc(char* fileName, char* gpxSchemaFile){
    xmlDoc * doc = NULL;
    xmlNode * root_element = NULL;

    if(fileName == NULL || gpxSchemaFile == NULL){
        return NULL;
    }

    /*parse the file and get the DOM */
    doc = xmlReadFile(fileName, NULL, 0);

    if (doc == NULL) {
        /*
        *Free the global variables that may
        *have been allocated by the parser.
        */
        xmlCleanupParser();
        return NULL;
    }

    if(schema_valid(doc, gpxSchemaFile)){
        /*
        * this initialize the library and check potential ABI mismatches
        * between the version it was compiled for and the actual shared
        * library used.
        */
        LIBXML_TEST_VERSION

        GPXdoc * to_parse = malloc(sizeof(GPXdoc));


        /*Get the root element node */
        root_element = xmlDocGetRootElement(doc);

        to_parse->routes = initializeList(&routeToString, &deleteRoute, &compareRoutes);
        to_parse->tracks = initializeList(&trackToString, &deleteTrack, &compareTracks);
        to_parse->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);

        parse(to_parse, root_element);

        xmlFreeDoc(doc);
        xmlSchemaCleanupTypes();
        xmlCleanupParser();
        xmlMemoryDump();

        return to_parse;
    }

    xmlFreeDoc(doc);
    xmlSchemaCleanupTypes();
    xmlCleanupParser();
    xmlMemoryDump();

    return NULL;
}

/** Function to validating an existing a GPXobject object against a GPX schema file
 *@pre
    GPXdoc object exists and is not NULL
    schema file name is not NULL/empty, and represents a valid schema file
 *@post GPXdoc has not been modified in any way
 *@return the boolean aud indicating whether the GPXdoc is valid
 *@param doc - a pointer to a GPXdoc struct
 *@param gpxSchemaFile - the name of a schema file
 **/
bool validateGPXDoc(GPXdoc* doc, char* gpxSchemaFile){
    if(doc == NULL){
        return false;
    }

    xmlDocPtr xmlDoc = convertToxml(doc);

    if(xmlDoc == NULL){
        xmlCleanupParser();
        xmlMemoryDump();
        return false;
    }

    bool output = xml_valid(doc);

    if(output == false){
        xmlCleanupParser();
        xmlMemoryDump();
        return false;
    }


    output = schema_valid(xmlDoc, gpxSchemaFile);

    if(output == false){
        xmlSchemaCleanupTypes();
        xmlCleanupParser();
        xmlMemoryDump();
        return false;
    }

    if(xmlDoc != NULL){
        /* free the document */
        xmlFreeDoc(xmlDoc);
    }
    xmlSchemaCleanupTypes();
    xmlCleanupParser();
    xmlMemoryDump();

    return output;
}

bool checkExtension(char * fileName){
    char last;
    char secL;
    char secF;
    char first;
    bool output = true;

    if(strlen(fileName) < 5){
        return false;
    }

    last = fileName[strlen(fileName)-1];
    secL = fileName[strlen(fileName)-2];
    secF = fileName[strlen(fileName)-3];
    first = fileName[strlen(fileName)-4];

    if((last != 'x') || (secL != 'p') || (secF != 'g') || (first != '.')){
        output = false;
    }
    return output;
}

/** Function to writing a GPXdoc into a file in GPX format.
 *@pre
    GPXdoc object exists, is valid, and and is not NULL.
    fileName is not NULL, has the correct extension
 *@post GPXdoc has not been modified in any way, and a file representing the
    GPXdoc contents in GPX format has been created
 *@return a boolean value indicating success or failure of the write
 *@param
    doc - a pointer to a GPXdoc struct
 	fileName - the name of the output file
 **/
bool writeGPXdoc(GPXdoc* doc, char* fileName){
    if(doc == NULL || fileName == NULL){
        return false;
    }

    if(checkExtension(fileName) == false){
        return false;
    }
    
    xmlDocPtr xmlDoc = convertToxml(doc);

    if(xmlDoc == NULL){
        /*
         *Free the global variables that may
         *have been allocated by the parser.
         */
        xmlCleanupParser();

        /*
         * this is to debug memory for regression tests
         */
        xmlMemoryDump();

        return false;
    }

    /*
     * Dumping document to stdio or file
     */
    if(xmlSaveFormatFileEnc(fileName, xmlDoc, "UTF-8", 1) ==-1){
        xmlFreeDoc(xmlDoc);
        xmlCleanupParser();
        xmlMemoryDump();
        return false;
    }

    xmlFreeDoc(xmlDoc);
    xmlCleanupParser();
    xmlMemoryDump();

    return true;
}


float distance(double src_lat, double src_lon, double dest_lat, double dest_lon){
    float lat_diff = (M_PI/180)*(src_lat - dest_lat);
    float lon_diff = (M_PI/180)*(src_lon - dest_lon);
    float radius = 6371e3;

    float radius_1 =(M_PI/180) * src_lat;
    float radius_2 = (M_PI/180) * dest_lat;

    float radicand = sin(lat_diff/2.) * sin(lat_diff/2.) +
            cos(radius_1) * cos(radius_2) *
            sin(lon_diff/2.) * sin(lon_diff/2.);

    return radius * asin(sqrt(radicand)) * 2;
}

float distance_points(Waypoint * pt1, Waypoint * pt2){
    if(pt1 == NULL || pt2 == NULL){
        return 0.0;
    }
    return distance(pt1->latitude, pt1->longitude, pt2->latitude, pt2->longitude);
}

/** Function that returns the length of a Route
 *@pre Route object exists, is not null, and has not been freed
 *@post Route object must not be modified in any way
 *@return length of the route in meters
 *@param rt - a pointer to a Route struct
**/
float getRouteLen(const Route *rt){
    if(rt == NULL || rt->waypoints == NULL){
        return 0.0;
    }

    if(getLength((List *) rt->waypoints) < 1){
        return 0.0;
    }

    float output = 0.0;
    Waypoint * pt1 = NULL;
    Waypoint * pt2 = NULL;
    ListIterator iter1 = createIterator((List *) rt->waypoints);
    ListIterator iter2 = createIterator((List *) rt->waypoints);

    pt2 = nextElement(&iter2);
    while((pt1 = nextElement(&iter1)) != NULL && (pt2 = nextElement(&iter2)) != NULL){
        if(pt1 != NULL && pt2 != NULL){
            output += distance_points(pt1, pt2);
        }
    }
    return output;
}

float segmentLen(TrackSegment * seg){
    if(seg == NULL || seg->waypoints == NULL){
        return 0.0;
    }

    if(getLength(seg->waypoints) < 1){
        return 0.0;
    }

    float output = 0.0;
    Waypoint * pt1 = NULL;
    Waypoint * pt2 = NULL;
    ListIterator iter1 = createIterator((List *) seg->waypoints);
    ListIterator iter2 = createIterator((List *) seg->waypoints);

    pt2 = nextElement(&iter2);
    while((pt1 = nextElement(&iter1)) != NULL && (pt2 = nextElement(&iter2)) != NULL){
        if(pt1 != NULL && pt2 != NULL){
            output += distance_points(pt1, pt2);
        }
    }
    return output;
}

/** Function that returns the length of a Track
 *@pre Track object exists, is not null, and has not been freed
 *@post Track object must not be modified in any way
 *@return length of the track in meters
 *@param tr - a pointer to a Track struct
**/
float getTrackLen(const Track *tr){
    if(tr == NULL || tr->segments == NULL){
        return 0.0;
    }

    float output = 0.0;
    TrackSegment * current = NULL;
    TrackSegment * front = NULL;
    TrackSegment * back = NULL;
    Waypoint* first = NULL;
    Waypoint* last = NULL;

    ListIterator one = createIterator(tr->segments);
    ListIterator beg = createIterator(tr->segments);
    ListIterator end = createIterator(tr->segments);

    if(getLength(tr->segments) == 1){
        if((current = nextElement(&one)) != NULL){
            return segmentLen(current);
        }
    }

    back  = nextElement(&end);
    while((front = nextElement(&beg)) != NULL && (back  = nextElement(&end)) != NULL){
        output += segmentLen(front);
        output += segmentLen(back);

        first = getFromBack(front->waypoints);
        last = getFromFront(back->waypoints);

        if(first != NULL && last != NULL){
           output += distance_points(first, last);
        }
    }
    return output;
}

/** Function that rounds the length of a track or a route to the nearest 10m
 *@pre Length is not negative
 *@return length rounded to the nearest 10m
 *@param len - length
**/
float round10(float len){
    int rounded = (len+5)/10;
    rounded *= 10;
    return (float) rounded;
}

/** Function that returns the number routes with the specified length, using the provided tolerance
 * to compare route lengths
 *@pre GPXdoc object exists, is not null
 *@post GPXdoc object exists, is not null, has not been modified
 *@return the number of routes with the specified length
 *@param doc - a pointer to a GPXdoc struct
 *@param len - search route length
 *@param delta - the tolerance used for comparing route lengths
**/
int numRoutesWithLength(const GPXdoc* doc, float len, float delta){
    if(doc == NULL || doc->routes == NULL || len < 0 || delta < 0){
        return 0;
    }

    if(getLength((List *) doc->routes) < 1){
        return 0;
    }

    int count = 0;
    float distance = 0.0;
    Route * current = NULL;
    ListIterator iter = createIterator((List *) doc->routes);

    while((current = nextElement(&iter)) != NULL){
        distance = fabs(len - getRouteLen((const Route *) current));

        if(distance <= delta){
            count++;
        }
    }
    return count;
}


/** Function that returns the number tracks with the specified length, using the provided tolerance
 * to compare track lengths
 *@pre GPXdoc object exists, is not null
 *@post GPXdoc object exists, is not null, has not been modified
 *@return the number of tracks with the specified length
 *@param doc - a pointer to a GPXdoc struct
 *@param len - search track length
 *@param delta - the tolerance used for comparing track lengths
**/
int numTracksWithLength(const GPXdoc* doc, float len, float delta){
    if(doc == NULL || doc->tracks == NULL || len < 0 || delta < 0){
        return 0;
    }

    if(getLength((List *) doc->tracks) < 1){
        return 0;
    }

    int count = 0;
    float distance = 0.0;
    Track * current = NULL;
    ListIterator iter = createIterator((List *) doc->tracks);

    while((current = nextElement(&iter)) != NULL){
        distance = fabs(len - getTrackLen(current));

        if(distance <= delta){
            count++;
        }
    }
    return count;
}

/** Function that checks if the current route is a loop
 *@pre Route object exists, is not null
 *@post Route object exists, is not null, has not been modified
 *@return true if the route is a loop, false otherwise
 *@param route - a pointer to a Route struct
 *@param delta - the tolerance used for comparing distances between start and end points
**/
bool isLoopRoute(const Route* route, float delta){
    if(route == NULL || delta < 0){
        return false;
    }

    if(getLength(route->waypoints) < 4 || delta < 0){
        return false;
    }

    Waypoint * first = NULL;
    Waypoint * last = NULL;

    first = getFromFront(route->waypoints);
    last = getFromBack(route->waypoints);

    if(first != NULL && last != NULL){
        if(distance_points(first, last) <= delta){
            return true;
        }
    }

    return false;
}

void dummy_delete(){return;}

bool pointCheck(const Track * tr){
    int output = 0;
    TrackSegment * current = NULL;
    ListIterator more = createIterator(tr->segments);

    while((current = nextElement(&more)) != NULL){
        output += getLength(current->waypoints);
    }
    if(output < 4){
        return false;
    }
    return true;
}

/** Function that checks if the current track is a loop
 *@pre Track object exists, is not null
 *@post Track object exists, is not null, has not been modified
 *@return true if the track is a loop, false otherwise
 *@param track - a pointer to a Track struct
 *@param delta - the tolerance used for comparing distances between start and end points
**/
bool isLoopTrack(const Track *tr, float delta){
    if(tr == NULL || delta < 0){
        return false;
    }

    if(pointCheck(tr) == false){
        return false;
    }

    Waypoint* first = getFromFront(((TrackSegment*) getFromFront(tr->segments))->waypoints);
    Waypoint* last = getFromBack(((TrackSegment*) getFromBack(tr->segments))->waypoints);

    if(first != NULL && last != NULL){
        if(distance_points(first, last) <= delta){
            return true;
        }
    }
    return false;
}


/** Function that returns all routes between the specified start and end locations
 *@pre GPXdoc object exists, is not null
 *@post GPXdoc object exists, is not null, has not been modified
 *@return a list of Route structs that connect the given sets of coordinates
 *@param doc - a pointer to a GPXdoc struct
 *@param sourceLat - latitude of the start location
 *@param sourceLong - longitude of the start location
 *@param destLat - latitude of the destination location
 *@param destLong - longitude of the destination location
 *@param delta - the tolerance used for comparing distances between waypoints
*/
List* getRoutesBetween(const GPXdoc* doc, float sourceLat, float sourceLong, float destLat, float destLong, float delta){
    if (doc == NULL){
        return NULL;
    }

    if(delta < 0){
        return NULL;
    }

    float source = 0.0;
    float destination = 0.0;

    Route * current = NULL;
    Waypoint * last = NULL;
    Waypoint * first = NULL;
    ListIterator iter = createIterator((List *) doc->routes);
    List * routes_result = initializeList(&routeToString, &dummy_delete, &compareRoutes);

    while((current = nextElement(&iter)) != NULL){
        last = getFromBack(current->waypoints);
        first = getFromFront(current->waypoints);

        if(first != NULL && last != NULL){
            destination = distance(destLat, destLong, last->latitude, last->longitude);
            source = distance(sourceLat, sourceLong, first->latitude, first->longitude);

            if((destination <= delta) && (source <= delta)){
                insertBack(routes_result, current);
            }
        }
    }
    if(getLength(routes_result) == 0){
        freeList(routes_result);
        return NULL;
    }
    return routes_result;
}

/** Function that returns all Tracks between the specified start and end locations
 *@pre GPXdoc object exists, is not null
 *@post GPXdoc object exists, is not null, has not been modified
 *@return a list of Track structs that connect the given sets of coordinates
 *@param doc - a pointer to a GPXdoc struct
 *@param sourceLat - latitude of the start location
 *@param sourceLong - longitude of the start location
 *@param destLat - latitude of the destination location
 *@param destLong - longitude of the destination location
 *@param delta - the tolerance used for comparing distances between waypoints
*/
List* getTracksBetween(const GPXdoc* doc, float sourceLat, float sourceLong, float destLat, float destLong, float delta){
    if(doc == NULL || delta < 0){
        return NULL;
    }

    float source = 0.0;
    float destination = 0.0;
    Track * current = NULL;
    Waypoint * last = NULL;
    Waypoint * first = NULL;
    ListIterator iter = createIterator((List *) doc->tracks);
    List * tracks_result = initializeList(&trackToString, &dummy_delete, &compareTracks);

    while((current = nextElement(&iter)) != NULL){
        first = getFromFront(((TrackSegment*) getFromFront(current->segments))->waypoints);
        last = getFromBack(((TrackSegment*) getFromBack(current->segments))->waypoints);

        if(first != NULL && last != NULL){
            destination = distance(destLat, destLong, last->latitude, last->longitude);
            source = distance(sourceLat, sourceLong, first->latitude, first->longitude);

            if((destination <= delta) && (source <= delta)){
                insertBack(tracks_result, current);
            }
        }
    }
    if(getLength(tracks_result) == 0){
        freeList(tracks_result);
        return NULL;
    }
    return tracks_result;
}

/** Function to converting a Track into a JSON string
 *@pre Track is not NULL
 *@post Track has not been modified in any way
 *@return A string in JSON format
 *@param event - a pointer to a Track struct
 **/
char* trackToJSON(const Track *tr){
    if(tr == NULL){
        char * string = malloc(3);
        string[0] = '\0';
        strcpy(string, "{}");

        return string;
    }

    char * name = NULL;
    char * string = malloc(1024);

    if(tr->name == NULL || strcmp(tr->name, "") == 0){
        name = malloc(5);
        strcpy(name, "None");
    } else{
        name = malloc(strlen(tr->name) + 1);
        strcpy(name, tr->name);
    }

    float length = round10(getTrackLen(tr));
    bool loop = isLoopTrack(tr, 10.0);
    char loopVal[6];
 
    if(loop){
        strcpy(loopVal, "true");
    } else{
        strcpy(loopVal, "false");
    }

    sprintf(string, "{\"name\":\"%s\",\"len\":%.1f,\"loop\":%s}", name, length, loopVal);
    free(name);
    return string;
}

/** Function to converting a Route into a JSON string
 *@pre Route is not NULL
 *@post Route has not been modified in any way
 *@return A string in JSON format
 *@param event - a pointer to a Route struct
 **/
char* routeToJSON(const Route *rt){
    if(rt == NULL){
        char * string = malloc(3);
        string[0] = '\0';
        strcpy(string, "{}");
        return string;
    }

    char * name = NULL;
    char * string = malloc(1024);

    if(rt->name == NULL || strcmp(rt->name, "") == 0){
        name = malloc(5);
        name[0] = '\0';
        strcpy(name, "None");
    } else{
        name = malloc(strlen(rt->name) + 1);
        name[0] = '\0';
        strcpy(name, rt->name);
    }

    int num = getLength(rt->waypoints);
    float length = round10(getRouteLen(rt));
    bool loop = isLoopRoute(rt, 10.0);
    char loopVal[6];

    if(loop){
        strcpy(loopVal, "true");
    } else{
        strcpy(loopVal, "false");
    }

    sprintf(string, "{\"name\":\"%s\",\"numPoints\":%d,\"len\":%.1f,\"loop\":%s}", name, num, length, loopVal);
    free(name);
    return string;
}

/** Function to converting a list of Route structs into a JSON string
 *@pre Route list is not NULL
 *@post Route list has not been modified in any way
 *@return A string in JSON format
 *@param event - a pointer to a List struct
 **/
char* routeListToJSON(const List *list){
    if(list == NULL){
        char * string = malloc(3);
        string[0] = '\0';
        strcpy(string, "[]");
        return string;
    }

    Route * current = NULL;
    ListIterator iter = createIterator((List*)list);

    int count = 0;
    char * string = malloc(getLength((List *) list) * 1024);
    string[0] = '\0';
    strcpy(string, "[");

    while((current = nextElement(&iter)) != NULL){
        char * route = routeToJSON(current);

        strcat(string, route);
        if(count < (getLength((List *) list) - 1)){
            strcat(string, ",");
        }
        count++;
        free(route);
    }

    strcat(string, "]");
    return string;
}

/** Function to converting a list of Track structs into a JSON string
 *@pre Track list is not NULL
 *@post Track list has not been modified in any way
 *@return A string in JSON format
 *@param event - a pointer to a List struct
 **/
char* trackListToJSON(const List *list){
    if(list == NULL){
        char * string = malloc(3);
        string[0] = '\0';
        strcpy(string, "[]");
        return string;
    }

    Track * current = NULL;
    ListIterator iter = createIterator((List*) list);

    int count = 0;
    char * string = malloc(getLength((List *) list) * 1024);
    string[0] = '\0';
    strcpy(string, "[");

    while((current = nextElement(&iter)) != NULL){
        char * track = trackToJSON(current);

        strcat(string, track);
        if(count < (getLength((List *) list) - 1)){
            strcat(string, ",");
        }
        count++;
        free(track);
    }

    strcat(string, "]");
    return string;
}

/** Function to converting a GPXdoc into a JSON string
 *@pre GPXdoc is not NULL
 *@post GPXdoc has not been modified in any way
 *@return A string in JSON format
 *@param event - a pointer to a GPXdoc struct
 **/
char* GPXtoJSON(const GPXdoc* gpx){
    if(gpx == NULL){
        char * string = malloc(3);
        string[0] = '\0';
        strcpy(string, "{}");
        return string;
    }

    char *output = malloc(1024);
    output[0] = '\0';
    double version = gpx->version;
    int routes = getNumRoutes(gpx);
    int tracks = getNumTracks(gpx);
    int points = getNumWaypoints(gpx);

    sprintf(output, "{\"version\":%0.1f,\"creator\":\"%s\",\"numWaypoints\":%d,\"numRoutes\":%d,\"numTracks\":%d}", version, gpx->creator, points, routes, tracks);
    return output;

}

/** Function to adding an Waypont struct to an existing Route struct
 *@pre arguments are not NULL
 *@post The new waypoint has been added to the Route's waypoint list
 *@return N/A
 *@param rt - a Route struct
 *@param pr - a Waypoint struct
 **/
void addWaypoint(Route *rt, Waypoint *pt){
    if((rt != NULL) && (pt != NULL)){
        insertBack(rt->waypoints, pt);
    }
}

/** Function to adding an Route struct to an existing GPXdoc struct
 *@pre arguments are not NULL
 *@post The new route has been added to the GPXdoc's routes list
 *@return N/A
 *@param doc - a GPXdoc struct
 *@param rt - a Route struct
 **/
void addRoute(GPXdoc* doc, Route* rt){
    if((doc != NULL) && (rt != NULL)){
        insertBack(doc->routes, rt);
    }
}

int parseJSON(char *input, char **arguments){

    char *token;
    int argumentIndex = 0;
    const char *delimiter = ",\"{}:";

    /* get the first token */
    token = strtok(input, delimiter);
    arguments[argumentIndex] = token;
    argumentIndex++;

    /* walk through other tokens */
    while(token != NULL) {
        token = strtok(NULL, delimiter);
        if ( token != NULL ) {
            arguments[argumentIndex] = token;
            argumentIndex++;
        }
    }

    return argumentIndex;
}

/** Function to converting a JSON string into an GPXdoc struct
 *@pre JSON string is not NULL
 *@post String has not been modified in any way
 *@return A newly allocated and initialized GPXdoc struct
 *@param str - a pointer to a string
 **/
GPXdoc* JSONtoGPX(const char* gpxString){
    if(gpxString == NULL){
        return NULL;
    }

    GPXdoc *gpxdoc = malloc(sizeof(GPXdoc));
    gpxdoc->routes = initializeList(&routeToString, &deleteRoute, &compareRoutes);
    gpxdoc->tracks = initializeList(&trackToString, &deleteTrack, &compareTracks);
    gpxdoc->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
    strcpy(gpxdoc->namespace, "http://www.topografix.com/GPX/1/1");

    char ** parameters = malloc(1024);

    int length = parseJSON((char *)gpxString, parameters);

    if(length == 4){
        char * next;
        gpxdoc->creator = malloc(256);
        gpxdoc->version = strtod(parameters[1], &next);
        strcpy(gpxdoc->creator , parameters[3]);
    }

    free(parameters);
    return gpxdoc;
}

/** Function to converting a JSON string into an Waypoint struct
 *@pre JSON string is not NULL
 *@post String has not been modified in any way
 *@return A newly allocated and initialized Waypoint struct
 *@param str - a pointer to a string
 **/
Waypoint* JSONtoWaypoint(const char* gpxString){
    if(gpxString == NULL){
        return NULL;
    }

    Waypoint * point = malloc(sizeof(Waypoint));
    point->otherData = initializeList(&gpxDataToString, &deleteGpxData, &compareGpxData);

    char ** parameters = malloc(1024);
    int length = parseJSON((char *) gpxString, parameters);
    point->name = malloc(256);
    strcpy(point->name, "");

    if(length == 4){
        char * next;
        point->latitude = strtod(parameters[1], &next);
        point->longitude = strtod(parameters[3], &next);
    }
    free(parameters);
    return point;
}

/** Function to converting a JSON string into an Route struct
 *@pre JSON string is not NULL
 *@post String has not been modified in any way
 *@return A newly allocated and initialized Route struct
 *@param str - a pointer to a string
 **/
Route* JSONtoRoute(const char* gpxString){
    if(gpxString == NULL){
        return NULL;
    }

    Route *rte = malloc(sizeof(Route));
    rte->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
    rte->otherData = initializeList(&gpxDataToString, &deleteGpxData, &compareGpxData);

    char ** parameters = malloc(1024);

    int length = parseJSON((char *)gpxString, parameters);

    if(length == 2){
        rte->name = malloc(256);
        strcpy(rte->name , parameters[1]);
    }

    free(parameters);
    return rte;
}
// ===================== A3 ======================

char * validGPXJSON(char * nameOfFile){
    GPXdoc * doc = createValidGPXdoc(nameOfFile, "gpx.xsd");
    char * json = GPXtoJSON(doc);
    
    if(doc != NULL){
        deleteGPXdoc(doc);
    }
    return json;
}

GPXdoc validGPX(char * nameOfFile, char * schema){
    GPXdoc new = *createValidGPXdoc(nameOfFile, schema);;
    return new;
}

char * routes(char * nameOfFile){
    GPXdoc * doc = NULL;
    doc = createGPXdoc(nameOfFile);
    char * json = routeListToJSON(doc->routes);

    if(doc != NULL){
        deleteGPXdoc(doc);
    }

    return json;    
}

char * tracks(char * nameOfFile){
    GPXdoc * doc = NULL;
    doc = createGPXdoc(nameOfFile);
    char * json = trackListToJSON(doc->tracks);

    if(doc != NULL){
        deleteGPXdoc(doc);
    }
    return json;    
}

