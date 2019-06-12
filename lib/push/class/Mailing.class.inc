<?php

class Mailing extends ActiveRecord {

  const BAT_BASE_ID = 27;
  const NEWLSETTER_ID = 1;

  public function asCampaignHash() {
    $attrs = $this->getAttributes();
    $attrs['content_html'] = $this->getContentHtml();
    $attrs['content_text'] = $this->getContentText();
    $attrs['bases'] = array(self::BAT_BASE_ID);
    $attrs['newsletter_id'] = self::NEWLSETTER_ID;
    $attrs['status'] = $this->status > 0
                     ? Campaign::STATUS_SCHEDULED
                     : Campaign::STATUS_DRAFT;
    return $attrs;
  }

  public function getContentHtml() {
    $args = array('name' => $this->name,
                  'image' => $this->image,
                  'description' => $this->description,
                  'content' => $this->content);
    return Template::render($this->template, $args);
  }

  public function getContentText() {
    return '';
  }

  public function getStats() {
    $args = array('model_id' => I('mailing'),
                  'record_id' => $this->getId());
    if (!Campaign::exists($args)) return array();
    $campaign = Campaign::getInstance($args);
    if (!$campaign->isDelivered()) return array();
    return $campaign->getStats();
  }

}
