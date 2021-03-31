#include "GPXParser.h"

// // int convertToxml(GPXdoc * );
// // int validate_xml(xmlDocPtr , char *  );

// // int main(int argc, char **argv){
// //     //GPXdoc * test = createGPXdoc(argv[1]);
// //     GPXdoc * test = createValidGPXdoc(argv[1], "gpx.xsd");


// //     //Route  * newRte = getRoute(test, "Some route");


// //     Route * newRte = NULL;
// //     Track * newTrk = NULL;
// //     ListIterator iter1 = createIterator((List *) test->routes);
// //     ListIterator iter2 = createIterator((List *) test->tracks);
// //     char * tet = routeListToJSON(test->routes);
// //     char * tet2 = trackListToJSON(test->tracks);
// //     char * t = GPXtoJSON(test);
// //     // printf("%s\n", tet);
// //     free(tet);
// //     // printf("%s\n", tet2);
// //     free(tet2);
// //     // printf("%s\n", t);

// //     char strr[] = "{\"version\":1.1,\"creator\":\"WebTool\"}";
// //     char st[]= "{\"name\":\"Reynolds walk\"}";
// //     char s[] = "{\"lat\":43.537299,\"lon\":-80.218267}";

// //     GPXdoc * t2 = JSONtoGPX(strr);
// //     Route * r = JSONtoRoute(st);
// //     Waypoint * p = JSONtoWaypoint(s);

// //     printf("%f %s\n", t2->version, t2->creator);
// //     printf("%s\n", r->name);
// //     printf("%f %f\n", p->latitude, p->longitude);
// //     free(t);
// //     deleteGPXdoc(t2);
// //     deleteRoute(r);
// //     deleteWaypoint(p);
// //     // if((newRte = nextElement(&iter1)) ){ //&& (newTrk = nextElement(&iter2))
// //     //    // char * tet = routeListToJSON(newRte);
// //     //     char * tet2 = trackToJSON(newTrk);

// //     //     printf("%f\n", getRouteLen(newRte));
// //     //     printf("%f\n", getTrackLen(newTrk));
// //     //     printf("%d\n", numRoutesWithLength(test, 151, 10));
// //     //     printf("%d\n", numTracksWithLength(test, 380, 10));
// //     //     printf("%s\n", tet);
// //     //     printf("%s\n", tet2);

// //     //     free(tet2);
// //     //     free(tet);
// //     // }


// //     validateGPXDoc(test, "gpx.xsd");
// //     writeGPXdoc(test, "output.gpx");
// //     // printf("%f\n", round10(403));
// //     // printf("%f\n", round10(404));
// //     // printf("%f\n", round10(404.5));
// //     // printf("%f\n", round10(405));
// //     // printf("%f\n", round10(409));

// //     deleteGPXdoc(test);
// // }

// int main(int argc, char **argv) {
//     GPXdoc * doc = createValidGPXdoc(argv[1], "gpx.xsd");
//     bool validation = validateGPXDoc(doc, "gpx.xsd");
//         if(validation == false){
//             printf("Validation failed!\n");
//         }else{
//             writeGPXdoc(doc, "save.gpx");

//             Route * rt = NULL;
//             Track * tr = NULL;
//             rt = getFromFront(doc->routes);
//             tr = getFromFront(doc->tracks);
//             printf("Route Length: %f\n",getRouteLen(rt));
//             printf("Track Length: %f\n",getTrackLen(tr));

//             printf("Routes with Length 200 (d:50): %d\n",numRoutesWithLength(doc, 200, 50));
//             printf("Tracks with Length 300 (d:50): %d\n",numTracksWithLength(doc, 300, 50));


//             printf("Is first route loop: %d\n",isLoopRoute(getFromFront(doc->routes),10));
//             printf("Is first track loop: %d\n",isLoopTrack(getFromFront(doc->tracks),10));


//             //List * bRoutes = getRoutesBetween(doc, ((Waypoint *)getFromFront(rt->waypoints))->latitude, ((Waypoint *)getFromFront(rt->waypoints))->longitude, ((Waypoint *)getFromBack(rt->waypoints))->latitude, ((Waypoint *)getFromBack(rt->waypoints))->longitude, 10);
//             List * bTracks = getTracksBetween(doc, ((Waypoint *)getFromFront(((TrackSegment *)getFromFront(tr->segments))->waypoints))->latitude, ((Waypoint *)getFromFront(((TrackSegment *)getFromFront(tr->segments))->waypoints))->longitude,
//                                                     ((Waypoint *)getFromBack(((TrackSegment *)getFromBack(tr->segments))->waypoints))->latitude, ((Waypoint *)getFromBack(((TrackSegment *)getFromBack(tr->segments))->waypoints))->longitude, 10);

//             char * text = NULL;
//             // if(bRoutes != NULL){
//             //     // text = toString(bRoutes);
//             //     // printf("%s\n",text);
//             //     // free(text);
//             // }
//             if(bTracks != NULL){
//                 // text = toString(bTracks);
//                 // printf("%s\n",text);
//                 // free(text);
//             }

//             text = GPXtoJSON(doc);
//             printf("%s\n", text);
//             free(text);
//             text = routeToJSON(rt);
//             printf("%s\n", text);
//             free(text);
//             text = trackToJSON(tr);
//             printf("%s\n", text);
//             free(text);

//             // text = routeListToJSON(bRoutes);
//             // printf("%s\n", text);
//             // free(text);

//             text = trackListToJSON(bTracks);
//             printf("%s\n", text);
//             free(text);

//             clearList(bTracks);
//             free(bTracks);
//             // clearList(bRoutes);
//             // free(bRoutes);
//     }
//     deleteGPXdoc(doc);
//     return 0;
// }

// #include "GPXParser.h"

// int main(int argc, char * argv[]) {
//     GPXdoc * g = createValidGPXdoc("./testA2/testA2.gpx", "./gpx.xsd");
//     //GPXdoc * g = createValidGPXdoc("./testA2/simpleInvalid1.gpx", "./gpx.xsd");
//     printf("isValidGPXdoc: %d\n", validateGPXDoc(g, "gpx.xsd"));
//     writeGPXdoc(g, "simple_copy.gpx");
//
//     printf("Route distance: %f\n", getRouteLen(getRoute(g, "Some route")));
//     printf("Track distance: %f\n", getTrackLen(getTrack(g, "Mount Steele Trail")));
//
//     printf("Num routes: %d %d %d %d %d %d\n",
//             numRoutesWithLength(g, 315, 0.5),
//             numRoutesWithLength(g, 313, 1),
//             numRoutesWithLength(g, 312, 1),
//             numRoutesWithLength(g, 312, 2),
//             numRoutesWithLength(g, 312, 20),
//             numRoutesWithLength(g, 323, 10));
//
//     printf("Num tracks: %d %d %d %d\n",
//             numTracksWithLength(g, 337, .1),
//             numTracksWithLength(g, 337, .5),
//             numTracksWithLength(g, 338, .5),
//             numTracksWithLength(g, 338, 1));
//
//     printf("Is route loop: %d %d %d\n",
//             isLoopRoute(getRoute(g, "Some route"), 0),
//             isLoopRoute(getRoute(g, "Some route"), 10),
//             isLoopRoute(getRoute(g, "Some other route"), 1000));
//
//     List * l = getRoutesBetween(g, 44.595860, -123.620950, 44.595860, -123.620955, .0);
//     printf("Num routes between 1: %d\n", l == NULL ? 0 : getLength(l));
//     freeList(l);
//
//     l = getTracksBetween(g, 49.595850, -123.620950, 49.598350, -123.619520, 0);
//     printf("Num tracks between 1: %d\n", l == NULL ? 0 : getLength(l));
//     freeList(l);
//
//     char * gpxJson = GPXtoJSON(g);
//     printf("\nGPX JSON: '%s'\n", gpxJson);
//     free(gpxJson);
//
//     char * trkJson = trackToJSON(getFromFront(g->tracks));
//     printf("\nTrack JSON: '%s'\n", trkJson);
//     free(trkJson);
//
//     char * rteJson = routeToJSON(getFromFront(g->routes));
//     printf("\nRoute JSON:'%s'\n", rteJson);
//     free(rteJson);
//
//     char * rteListJson = routeListToJSON(g->routes);
//     printf("\nRoute List JSON: '%s'\n", rteListJson);
//     free(rteListJson);
//
//     char * trkListJson = trackListToJSON(g->tracks);
//     printf("\nTrack List JSON: '%s'\n", trkListJson);
//     free(trkListJson);
//
//     deleteGPXdoc(g);
//
//     char t1[] = "{\"version\":1.1,\"creator\":\"WebTool\"}";
//     char t2[] = "{\"name\":\"Reynolds walk\"}";
//     char t3[] = "{\"lat\":43.537299,\"lon\":-80.218267}\"}";
//     char t4[] = "{\"lat\":44.537299,\"lon\":-81.218267}\"}";
//
//
//     g = JSONtoGPX(t1);
//     Route * r = JSONtoRoute(t2);
//     Waypoint * p = JSONtoWaypoint(t3);
//     Waypoint * p2 = JSONtoWaypoint(t4);
//     addWaypoint(r, p);
//     addWaypoint(r, p2);
//     addRoute(g, r); // swg
//     char * str = GPXdocToString(g);
//
//     printf("\nCheck \"fromJSONs.gpx\" and make sure it matches (output will vary here based on GPXdocToString()):\n%s\n", str);
//     writeGPXdoc(g, "fromJSONs.gpx");
//     free(str);
//     deleteGPXdoc(g);
//
//     if (JSONtoRoute(NULL) != NULL) printf("Bad return with NULL argument\n");
//     if (JSONtoWaypoint(NULL) != NULL) printf("Bad return with NULL argument\n");
//     if (JSONtoGPX(NULL) != NULL) printf("Bad return with NULL argument\n");
// }

int main(int argc, char **argv) {
    // GPXdoc * doc = createValidGPXdoc(argv[1], "./gpx.xsd");
    // printf("%d\n", writeGPXdoc(doc, ".gpx"));
    Route *routePtrFirst = NULL, *routePtrLast = NULL;
    Track *trackPtrFirst = NULL, *trackPtrLast = NULL;

    printf("\n1. Testing 'createValidGPXdoc' with valid arguments...\n");
    GPXdoc *doc = createValidGPXdoc(argv[1], "./gpx.xsd");
    if(doc) printf("\tCreated valid GPXdoc.\n");
    else {
        printf("\tCreated invalid GPXdoc... exiting program.\n");
        return 0;
    }

    routePtrFirst = getFromFront(doc->routes);
    routePtrLast = getFromBack(doc->routes);

    trackPtrFirst = getFromFront(doc->tracks);
    trackPtrLast = getFromBack(doc->tracks);

    printf("\n2. Testing 'validateGPXDoc' with valid arguments...\n");
    bool isValid = validateGPXDoc(doc, "./gpx.xsd");
    if(isValid) printf("\tValid GPXdoc.\n");
    else printf("\tInvalid GPXdoc.\n");

    printf("\n3. Testing 'writeGPXdoc' with valid arguments...\n");
    bool didWrite = writeGPXdoc(doc, "output.gpx");
    if(didWrite) printf("\tSuccesfully wrote GPXdoc to fileName output.gpx.\n");
    else printf("\tCouldn't write GPXdoc succesfully.\n");

    printf("\n4. Testing 'getRouteLen' with '%s'...\n", routePtrFirst->name);
    float routeLen = getRouteLen(routePtrFirst);
    printf("\t'%s' route len is %f, round10 is %f.\n", routePtrFirst->name, routeLen, round10(routeLen));

    printf("\n5. Testing getTrackLen with %s...\n", trackPtrFirst->name);
    float trackLen = getTrackLen(trackPtrFirst);
    printf("\t'%s' track len is %f. round10 is %f.\n", trackPtrFirst->name, trackLen, round10(trackLen));

    float delta = 11.0;
    printf("\n6. Testing numRoutesWithLength with '%f' and delta '%f'...\n",
           routeLen + delta, delta);
    int numRoutes = numRoutesWithLength(doc, routeLen+delta, delta);
    printf("\t%d routes with length %f +- %f.\n", numRoutes, routeLen, delta);

    delta = 10.0;
    printf("\n7. Testing numRoutesWithLength with '%f' and delta '%f'...\n", routeLen-delta-1, 10.0);
    numRoutes = numRoutesWithLength(doc, routeLen-delta-1, delta);
    printf("\t%d routes with length %f +- %f.\n", numRoutes, routeLen, delta+1);

    delta = 8.0;
    printf("\n8. Testing numTracksWithLength with '%f' and delta '%f'...\n", trackLen+delta, delta);
    int numTracks = numTracksWithLength(doc, trackLen+delta, delta);
    printf("\t%d routes with length %f +- %f.\n", numTracks, trackLen, delta);

    delta = 7.0;
    printf("\n9. Testing numTracksWithLength with '%f' and delta '%f'...\n",
           trackLen - delta - 1, delta);
    numTracks = numTracksWithLength(doc, trackLen-delta-1, delta);
    printf("\t%d routes with length %f +- %f.\n", numTracks, trackLen, delta);

    printf("\n10. Testing isLoopRoute with '%s' and delta 10...\n", routePtrFirst->name);
    isLoopRoute(routePtrFirst, 10.0)
        ? printf("\t'%s' is loop route.\n", routePtrFirst->name)
        : printf("\t '%s' isn't loop route.\n", routePtrFirst->name);

    printf("\n10.1 Testing isLoopRoute with '%s' and delta 10...\n",
           routePtrLast->name);
    isLoopRoute(routePtrLast, 10.0)
        ? printf("\t'%s' is loop route.\n", routePtrLast->name)
        : printf("\t '%s' isn't loop route.\n", routePtrLast->name);

    printf("\n11. Testing isLoopRoute with '%s' and delta 10000...\n", routePtrFirst->name);
    isLoopRoute(routePtrFirst, 10000.0)
        ? printf("\t'%s' is loop route.\n", routePtrFirst->name)
        : printf("\t '%s' isn't loop route.\n", routePtrFirst->name);

    printf("\n12. Testing isLoopTrack with '%s' and delta 10...\n",
           trackPtrFirst->name);
    isLoopTrack(trackPtrFirst, 10.0)
        ? printf("\t'%s' is loop track.\n", trackPtrFirst->name)
        : printf("\t '%s' isn't loop track.\n", trackPtrFirst->name);

    printf("\n12.1 Testing isLoopTrack with '%s' and delta 10...\n",
           trackPtrLast->name);
    isLoopTrack(trackPtrLast, 10.0)
        ? printf("\t'%s' is loop track.\n", trackPtrLast->name)
        : printf("\t '%s' isn't loop track.\n", trackPtrLast->name);

    printf("\n13. Testing isLoopTrack with '%s' and delta 10000...\n",
           trackPtrFirst->name);
    isLoopTrack(trackPtrFirst, 10000.0)
        ? printf("\t'%s' is loop track.\n", trackPtrFirst->name)
        : printf("\t '%s' isn't loop track.\n", trackPtrFirst->name);

    Waypoint *firstWp = getFromFront(routePtrFirst->waypoints);
    Waypoint *secondWp = getFromBack(routePtrLast->waypoints);

    printf(
        "\n14. Testing getRoutesBetween with sourceLat=%f, sourceLon=%f, "
        "destLat=%f, destLong=%f and delta=%f\n",
        firstWp->latitude, firstWp->longitude, secondWp->latitude,
        secondWp->longitude, 5.0);
    List *routesBetween =
        getRoutesBetween(doc, firstWp->latitude, firstWp->longitude,
                         secondWp->latitude, secondWp->longitude, 5.0);
    routesBetween
        ? printf("\tLength of routes between is %d.\n", routesBetween->length)
        : printf("\tList was NULL.\n");

    printf(
        "\n15. Testing getRoutesBetween with sourceLat=%f, sourceLon=%f, "
        "destLat=%f, destLong=%f and delta=%f\n",
        firstWp->latitude, firstWp->longitude, 44.596100, 123.620570, 5.0);
    List *routesBetween2 = getRoutesBetween(
        doc, firstWp->latitude, firstWp->longitude, 44.596100, -123.620570, 5.0);
    routesBetween2
        ? printf("\tLength of routes between is %d.\n", routesBetween2->length)
        : printf("\tList was NULL.\n");

    TrackSegment *firstTrackSeg = getFromFront(trackPtrFirst->segments);
    TrackSegment *lastTrackSeg = getFromBack(trackPtrLast->segments);

    firstWp = getFromFront(firstTrackSeg->waypoints);
    secondWp = getFromBack(lastTrackSeg->waypoints);

    printf(
        "\n16. Testing getTracksBetween with sourceLat=%f, sourceLon=%f, "
        "destLat=%f, destLong=%f and delta=%f\n",
        firstWp->latitude, firstWp->longitude, secondWp->latitude,
        secondWp->longitude, 5.0);
    List *tracksBetween =
        getTracksBetween(doc, firstWp->latitude, firstWp->longitude,
                         secondWp->latitude, secondWp->longitude, 5.0);
    tracksBetween
        ? printf("\tLength of tracks between is %d.\n", tracksBetween->length)
        : printf("\tList was NULL.\n");

    printf(
        "\n17. Testing getTracksBetween with sourceLat=%f, sourceLon=%f, "
        "destLat=%f, destLong=%f and delta=%f\n",
        firstWp->latitude, firstWp->longitude, 49.598070, -123.620460, 5.0);
    List *tracksBetween2 = getTracksBetween(doc, firstWp->latitude, firstWp->longitude,
                                     49.598070, -123.620460, 5.0);
    tracksBetween2
        ? printf("\tLength of tracks between is %d.\n", tracksBetween2->length)
        : printf("\tList was NULL.\n");

    char *t1ToJson = trackToJSON(trackPtrFirst);
    char *t2ToJson = trackToJSON(trackPtrLast);
    char *r1ToJson = routeToJSON(routePtrFirst);
    char *r2ToJson = routeToJSON(routePtrLast);
    char *rlToJson = routeListToJSON(doc->routes);
    char *tlToJson = trackListToJSON(doc->tracks);
    char *docToJson = GPXtoJSON(doc);

    printf("\n18. Testing trackToJson with '%s'...\n", trackPtrFirst->name);
    printf("\t'%s' is output string.\n", t1ToJson);
    printf("\n19. Testing trackToJson with '%s'...\n", trackPtrLast->name);
    printf("\t'%s' is output string.\n", t2ToJson);
    printf("\n20. Testing trackToJson with '%s'...\n", routePtrFirst->name);
    printf("\t'%s' is output string.\n", r1ToJson);
    printf("\n21. Testing trackToJson with '%s'...\n", routePtrLast->name);
    printf("\t'%s' is output string.\n", r2ToJson);
    printf("\n22. Testing routeListToJson...\n");
    printf("\t'%s' is output string.\n", rlToJson);
    printf("\n23. Testing trackListToJson...\n");
    printf("\t'%s' is output string.\n", tlToJson);
    printf("\n24. Testing docToJson...\n");
    printf("\t'%s' is output string.\n", docToJson);

    free(t1ToJson);
    free(t2ToJson);
    free(r1ToJson);
    free(r2ToJson);
    free(rlToJson);
    free(tlToJson);
    free(docToJson);

    freeList(routesBetween);
    freeList(tracksBetween);
    freeList(routesBetween2);
    freeList(tracksBetween2);

    deleteGPXdoc(doc);

    printf("\n\n");

    return 0;
}
