<?php

try {

  $page = Page::getInstance('fo.plan');

  /*$heading = Heading::getInstance(array('code' => 'ntd.articles'));
  $ctx->actu_pages = Article::collect(array('filters' => array('heading_id' => $heading->getId()),
                                            'order' => array('published_at' => 'DESC')));

  $heading = Heading::getInstance(array('code' => 'ntd.carousels'));
  $heading2 = Heading::getInstance(array('code' => 'ntd.pages'));
  */
  /*$ctx->headings = Heading::collect(array('filters' => array('|>|status' => 0,
                                                             '|!IN|name' => array('Front - Actions'))));
*/
  $urls = array();
  foreach (NetDeclaration::getTreeContent() as $node) {
    if ($node['node']['code'] == 'services') continue;
    $urls[$node['item']['url']] = $node['node']['name'];

    foreach ((array) $node['children'] as $child) {
      $urls[$child['item']['url']] = $child['node']['name'];
    }
  }
  foreach (NetDeclaration::getTreeFooter() as $root_node) {
    $urls[$root_node['item']['url']] = $root_node['node']['name'];
    foreach ((array) $root_node['children'] as $node) {
      $urls[$node['item']['url']] = $node['node']['name'];
    }
  }

  $headings_fronts = array(
    //303, // ntd.front.actions
    300, // ntd.carousels
    //297, // ntd.pages
  );
  foreach (Page::collect(array('filters' => array('|IN|heading_id' => $headings_fronts))) as $_page) {
    $urls[$_page->asUrl()] = $_page->title;
  }

  asort($urls);
  $ctx->urls = $urls;


  $servicetypes = array();
  foreach (Servicetype::collect(array('filters' => array('status' => 1))) as $_servicetype) {
    $servicetype = array('title' => $_servicetype->getProperty('title'),
                         'url' => $_servicetype->asUrl(),
                         'services' => array());
    foreach ($_servicetype->getServices(array('|>|status' => 0,
                                              'order' => array('type' => 'ASC'))) as $service) {
      $servicetype['services'][] = array('title' => $service->getProperty('title'),
                                         'url' => $service->asUrl());
    }
    asort($servicetype['services']);
    $servicetypes[] = $servicetype;
  }

  $ctx->servicetypes = $servicetypes;

  $req->track('plan du site', 'ntd');
  $res->setSeo($page);
  $res->setBreadcrumb(array('page d\'accueil' => '/',
                            $page->title => $page->asUrl()));
  $res->useTemplate();

}
catch (Exception $e) {
  $err->add($e);
}
